
#include <QtDebug>

#include "xymonwidget.h"
#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QMaemo5InformationBox>
#include <QFile>
#include <QDateTime>

XymonWidget::XymonWidget(QWidget *parent) :
	QWidget(parent)
{
	qDebug() << QString("XymonWidget::XymonWidget()");
	resize(144,178);
	setMinimumSize(144,178);
	setMaximumSize(144,178);

	m_lastMessage = "";
	QVBoxLayout *layout = new QVBoxLayout();
	m_colorLabel = new QLabel();
	m_colorLabel->setAlignment(Qt::AlignCenter);
	m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_blue.png")));
	m_currentColor = "blue";
	m_colorLabel->setContentsMargins(0,8,0,0);
	layout->addWidget(m_colorLabel);
	m_label = new QLabel();
	m_label->setAlignment(Qt::AlignCenter);
	layout->addWidget(m_label);
	setLayout(layout);
	m_timer = new QTimer();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(reloadStatus()));
	QSettings settings;
	QString txt = settings.value("poll_interval", QString("2 min")).toString();
	int secs = pollIntervalTextToSeconds(txt);
	qDebug() << QString("setting timer for %1 milliseconds").arg(secs * 1000);
	m_timer->start(secs * 1000);
	m_consecutiveTimeouts = 0;
	reload();
}

XymonWidget::~XymonWidget()
{
	qDebug() << QString("XymonWidget::~XymonWidget()");
}

void XymonWidget::showSettingsDialog()
{
	qDebug() << QString("XymonWidget::showSettingsDialog()");
	m_timer->stop();
	int ret = SettingsDialog().exec();
	if (ret == 1) {
		reload();
	}
	QSettings settings;
	QString txt = settings.value("poll_interval", QString("2 min")).toString();
	int secs = pollIntervalTextToSeconds(txt);
	qDebug() << QString("setting timer for %1 milliseconds").arg(secs * 1000);
	m_timer->start(secs * 1000);
}

void XymonWidget::reload()
{
	QSettings settings;
	m_serverAddress = settings.value("server_address", QString("")).toString();
	m_nickname = settings.value("nickname", QString("none")).toString();
	m_label->setText(m_nickname);
	if (settings.value("first_time_configured").toBool()) {
		reloadStatus();
	}
}

void XymonWidget::reloadStatus()
{
	QSettings settings;
	if (settings.value("needs_reconfigured").toBool()) {
		qDebug() << QString("can not fetch until reconfigured");
		m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_black.png")));
		m_currentColor = "black";
		return;
	}
	QString server_address = settings.value("server_address").toString();
	QRegExp re("https?://.*");
	if (!re.exactMatch(server_address)) {
		server_address = QString("http://%1").arg(server_address);
	}
	QNetworkAccessManager *man = new QNetworkAccessManager(this);
	QString urlstring = QString("%1/bb2.html").arg(server_address);
	QUrl url(urlstring);
	qDebug() << QString("fetching %1").arg(urlstring);
	connect(man, SIGNAL(finished(QNetworkReply *)), this, SLOT(haveReply(QNetworkReply *)));
	QNetworkRequest req(url);
	QString username = settings.value("username", QString("")).toString();
	QString password = settings.value("password", QString("")).toString();
	if (username.length() > 0) {
		QByteArray text;
		text.append(QString("%1:%2").arg(username).arg(password));
		QByteArray b64auth = text.toBase64();
		req.setRawHeader(QByteArray("Authorization"), QByteArray().append(QString("Basic %1").arg(QString(b64auth))));
	}
	man->get(req);
}

void XymonWidget::haveReply(QNetworkReply *reply)
{
	m_lastMessage = "";
	qDebug() << QString("have reply!");
	touchLastUpdated();
	#ifndef DEBUG
	if (reply->error() == 0) {
	#endif
		int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		#ifndef DEBUG
		if (status != 200) {
			QMaemo5InformationBox::information(this, QString("Received status: %1").arg(status), QMaemo5InformationBox::DefaultTimeout);
			m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_black.png")));
			m_currentColor = "black";

		} else {
			QByteArray data = reply->readAll();
			QString data_string(data);
		#else
			qDebug() << QString("testing file bb2.html locally");
			QFile f("bb2.html");
			f.open(QIODevice::ReadWrite | QIODevice::Text);
			QString data_string(f.readAll());
		#endif
			QRegExp re(QString(".*BODY BGCOLOR=\"(\\w+)\".*"));
			if (re.exactMatch(data_string)) {
				QString color = re.cap(1);
				m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_%1.png").arg(color)));
				m_currentColor = color;
				if (m_currentColor != "green") {
					qDebug() << QString("color wasn't green");
					QRegExp re(QString("<A[^>]*HOST=([a-zA-Z.]+)[^>]*><IMG[^>]*ALT=\"([a-zA-Z0-9_:]+)\""));
					int pos = 0;
					QStringList list;
					while ((pos = re.indexIn(data_string, pos)) != -1) {
						qDebug() << QString("match: %1").arg(re.cap(0));
						QString matched_string = QString("%1#%2").arg(re.cap(1)).arg(re.cap(2));
						qDebug() << matched_string;
						list << matched_string;
						pos += re.matchedLength();
					}
					qDebug() << list;
					QString message = "";
					for (int i = 0; i < list.size(); i++) {
						QString match = list[i];
						QStringList matchparts = match.split("#");
						QString host = matchparts[0];
						QString data = matchparts[1];
						QStringList dataparts = data.split(":", QString::KeepEmptyParts);
						QString svc = dataparts[0];
						QString color = dataparts[1];
						QString mdata = dataparts[2];
						if (color != "green") {
							message = QString("%1<br />%2 : %3 : %4 : %5").arg(message).arg(host).arg(svc).arg(color).arg(mdata);
						}
					}
					message = QString("%1<br />").arg(message);
					m_lastMessage = message;
				}
			} else {
				// no match
			}
		#ifndef DEBUG
		}
	} else {
		int error_code = reply->error();
		m_lastMessage = reply->errorString();
		m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_black.png")));
		m_currentColor = "black";
		if (!(error_code == QNetworkReply::TimeoutError)) {
			needsReconfigured();
		} else {
			m_consecutiveTimeouts += 1;
			m_lastMessage = QString("Request timed out (%1 times)").arg(m_consecutiveTimeouts);
		}
		if (m_consecutiveTimeouts > 3) {
			m_lastMessage = QString("Request timed out %1 times<br />Please check configuration.").arg(m_consecutiveTimeouts);
			needsReconfigured();
		}
		// error
	}
	#endif
	m_lastMessage = QString("%1<br /><span style=\"font-size: 0.8em;\">Last updated: %2</span><br />").arg(m_lastMessage).arg(lastUpdated());
}

QString XymonWidget::lastUpdated()
{
	QSettings settings;
	return(settings.value("last_updated", QString("never")).toString());
}

void XymonWidget::touchLastUpdated()
{
	QSettings settings;
	settings.setValue("last_updated", QDateTime::currentDateTime().toString());
	settings.sync();
}

void XymonWidget::needsReconfigured()
{
	QSettings settings;
	settings.setValue("needs_reconfigured", true);
	settings.sync();
}

int XymonWidget::pollIntervalTextToSeconds(const QString &txt)
{
	if (txt == "1 hr") {
		return(60 * 60);
	} else if (txt == "30 min") {
		return(30 * 60);
	} else if (txt == "15 min") {
		return(15 * 60);
	} else if (txt == "10 min") {
		return(10 * 60);
	} else if (txt == "5 min") {
		return(5 * 60);
	} else {
		return(2 * 60);
	}
}

void XymonWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_currentColor == "black") {
		QSettings settings;
		if (settings.value("needs_reconfigured").toBool()) {
			QMaemo5InformationBox::information(this, m_lastMessage, QMaemo5InformationBox::DefaultTimeout);
		} else {
			QMaemo5InformationBox::information(this, QString("%1<br />Refreshing.").arg(m_lastMessage), QMaemo5InformationBox::DefaultTimeout);
			reloadStatus();
		}
	} else if (m_currentColor != "green") {
		QMaemo5InformationBox::information(this, m_lastMessage, QMaemo5InformationBox::DefaultTimeout);
	} else {
		QMaemo5InformationBox::information(this, m_lastMessage, QMaemo5InformationBox::DefaultTimeout);
	}
}

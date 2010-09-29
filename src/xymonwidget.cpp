
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

XymonWidget::XymonWidget(QWidget *parent) :
	QWidget(parent)
{
	qDebug() << QString("XymonWidget::XymonWidget()");
	resize(144,178);
	setMinimumSize(144,178);
	setMaximumSize(144,178);

	QVBoxLayout *layout = new QVBoxLayout();
	m_colorLabel = new QLabel();
	m_colorLabel->setAlignment(Qt::AlignCenter);
	m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_blue.png")));
	layout->addWidget(m_colorLabel);
	m_label = new QLabel();
	m_label->setAlignment(Qt::AlignCenter);
	layout->addWidget(m_label);
	setLayout(layout);
	reload();
}

XymonWidget::~XymonWidget()
{
	qDebug() << QString("XymonWidget::~XymonWidget()");
}

void XymonWidget::showSettingsDialog()
{
	qDebug() << QString("XymonWidget::showSettingsDialog()");
	int ret = SettingsDialog().exec();
	if (ret == 1) {
		reload();
	}
}

void XymonWidget::reload()
{
	QSettings settings;
	m_serverAddress = settings.value("server_address", QString("")).toString();
	m_nickname = settings.value("nickname", QString("none")).toString();
	m_label->setText(m_nickname);

	reloadStatus();
}

void XymonWidget::reloadStatus()
{
	QSettings settings;
	QString server_address = settings.value("server_address").toString();
	QNetworkAccessManager *man = new QNetworkAccessManager(this);
	QUrl url(QString("%1/bb2.html").arg(server_address));
	QMaemo5InformationBox::information(this, QString("fetching %1").arg(url.toString()), QMaemo5InformationBox::NoTimeout);
	qDebug() << QString("fetching %1").arg(url.toString());
	connect(man, SIGNAL(finished(QNetworkReply *)), this, SLOT(haveReply(QNetworkReply *)));
	man->get(QNetworkRequest(url));
}

void XymonWidget::haveReply(QNetworkReply *reply)
{
	QMaemo5InformationBox::information(this, QString("have reply!"), QMaemo5InformationBox::NoTimeout);
	qDebug() << QString("have reply!");
	if (reply->error() == 0) {
		QMaemo5InformationBox::information(this, QString("no error"), QMaemo5InformationBox::NoTimeout);
		QByteArray data = reply->readAll();
		QString data_string(data);
		qDebug() << QString("%1").arg(data_string);
		QRegExp re(QString(".*BODY BGCOLOR=\"(.*?)\".*"));
		if (re.exactMatch(data_string)) {
			QString color = re.cap(1);
			QMaemo5InformationBox::information(this, QString("color: %1").arg(color), QMaemo5InformationBox::NoTimeout);
			m_colorLabel->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_%1.png").arg(color)));
		} else {
			QMaemo5InformationBox::information(this, QString("no match"), QMaemo5InformationBox::NoTimeout);
		}
	} else {
		QMaemo5InformationBox::information(this, QString("error: %1").arg(reply->error()), QMaemo5InformationBox::NoTimeout);
	}
}


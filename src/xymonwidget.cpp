
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

XymonWidget::XymonWidget(QWidget *parent) :
	QWidget(parent)
{
	qDebug() << QString("XymonWidget::XymonWidget()");
	resize(144,178);
	setMinimumSize(144,178);
	setMaximumSize(144,178);

	QVBoxLayout *layout = new QVBoxLayout();
	QLabel *w = new QLabel();
	w->setAlignment(Qt::AlignCenter);
	w->setPixmap(QPixmap(QString("/opt/xymon-widget/images/xymon_blue.png")));
	layout->addWidget(w);
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
	qDebug() << QString("fetching %1").arg(url.toString());
	connect(man, SIGNAL(finished(QNetworkReply *)), this, SLOT(haveReply(QNetworkReply *)));
	man->get(QNetworkRequest(url));
}

void XymonWidget::haveReply(QNetworkReply *reply)
{
	qDebug() << QString("have reply!");
}


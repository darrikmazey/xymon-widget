
#include <QtDebug>

#include "xymonwidget.h"
#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QSettings>

XymonWidget::XymonWidget(QWidget *parent) :
	QWidget(parent)
{
	qDebug() << QString("XymonWidget::XymonWidget()");
	resize(144,178);

	QVBoxLayout *layout = new QVBoxLayout();
	QWidget *w = new QWidget();
	w->setMinimumSize(144,148);
	w->setMaximumSize(144,148);
	layout->addWidget(w);
	QPalette p;
	p.setColor(QPalette::Window, QColor(0, 0, 255));
	w->setPalette(p);
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
}


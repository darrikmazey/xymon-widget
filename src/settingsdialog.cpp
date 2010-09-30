
#include <QtDebug>

#include "settingsdialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent, Qt::WindowFlags f) :
	QDialog(parent, f)
{
	setWindowTitle("Xymon Widget Settings");
	createControls();
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::createControls()
{
	QSettings settings;

	QHBoxLayout *layout = new QHBoxLayout();
	QVBoxLayout *col1 = new QVBoxLayout();

	QHBoxLayout *line1 = new QHBoxLayout();
	QLabel *lblNickname = new QLabel("Nickname");
	m_leNickname = new QLineEdit();

	m_leNickname->setText(settings.value("nickname", QString("")).toString());

	line1->addWidget(lblNickname);
	line1->addWidget(m_leNickname);
	col1->addLayout(line1);

	QHBoxLayout *line2 = new QHBoxLayout();
	QLabel *lblServerAddress = new QLabel("Server Address:");
	m_leServerAddress = new QLineEdit();

	m_leServerAddress->setText(settings.value("server_address", QString("no server")).toString());

	line2->addWidget(lblServerAddress);
	line2->addWidget(m_leServerAddress);
	col1->addLayout(line2);

	QHBoxLayout *line3 = new QHBoxLayout();
	QLabel *lblUsername = new QLabel("Username:");
	m_leUsername = new QLineEdit();

	m_leUsername->setText(settings.value("username", QString("")).toString());

	line3->addWidget(lblUsername);
	line3->addWidget(m_leUsername);
	col1->addLayout(line3);

	QHBoxLayout *line4 = new QHBoxLayout();
	QLabel *lblPassword = new QLabel("Password:");
	m_lePassword = new QLineEdit();

	m_lePassword->setText(settings.value("password", QString("")).toString());

	line4->addWidget(lblPassword);
	line4->addWidget(m_lePassword);
	col1->addLayout(line4);

	QVBoxLayout *col2 = new QVBoxLayout();
	QPushButton *btnSave = new QPushButton("Save");
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));
	col2->addWidget(btnSave);
	col2->addStretch();

	layout->addLayout(col1);
	layout->addLayout(col2);

	setLayout(layout);
}

void SettingsDialog::save()
{
	qDebug() << QString("SettingsDialog::save()");
	QSettings settings;
	settings.setValue("nickname", m_leNickname->text());
	settings.setValue("server_address", m_leServerAddress->text());
	settings.setValue("username", m_leUsername->text());
	settings.setValue("password", m_lePassword->text());
	settings.setValue("first_time_configured", true);
	settings.setValue("needs_reconfigured", false);
	settings.sync();
	emit accept();
}

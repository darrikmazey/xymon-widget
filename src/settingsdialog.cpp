
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
	settings.sync();
	emit accept();
}

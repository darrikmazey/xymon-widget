
#include <QtDebug>

#include "application.h"

#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

SettingsDialog::SettingsDialog(QWidget *parent, Qt::WindowFlags f) :
	QDialog(parent, f)
{
	qDebug() << QString("SettingsDialog::SettingsDialog()");
	createControls();
	setModal(true);
}

SettingsDialog::~SettingsDialog()
{
	qDebug() << QString("SettingsDialog::~SettingsDialog()");
}

void SettingsDialog::createControls()
{
	QHBoxLayout *layout = new QHBoxLayout();
	QVBoxLayout *col1 = new QVBoxLayout();
	QVBoxLayout *col2 = new QVBoxLayout();
	QPushButton *btnSave = new QPushButton(QString("Save"), this);
	btnSave->setDefault(true);
	connect(btnSave, SIGNAL(clicked()), this, SLOT(saveAndClose()));
	col2->addWidget(btnSave);

	QLabel *lblServer = new QLabel(QString("xymon server address"));
	m_txtServer = new QLineEdit();
	m_txtServer->setText(dApp->serverAddress());
	col1->addWidget(lblServer);
	col1->addWidget(m_txtServer);

	layout->addLayout(col1);
	layout->addLayout(col2);
	setLayout(layout);
}

void SettingsDialog::saveAndClose()
{
	dApp->setServerAddress(m_txtServer->text());
	this->done(QDialog::Accepted);
}

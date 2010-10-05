/****************************************************************************
**
** Copyright (C) 2010 DarmaSoft, LLC.
** All rights reserved.
** Contact: Darrik Mazey (darrik@darmasoft.com)
**
** This file is part of Xymon-Widget.
**
** Xymon-Widget is free software: you you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** Xymon-Widget is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with Xymon-Widget.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include <QtDebug>

#include "settingsdialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMaemo5ValueButton>
#include <QMaemo5ListPickSelector>
#include <QStringList>
#include <QStringListModel>

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

	QScrollArea *scroll = new QScrollArea(this);

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

	QHBoxLayout *line4 = new QHBoxLayout();
	QLabel *lblPassword = new QLabel("Password:");
	m_lePassword = new QLineEdit();

	m_lePassword->setText(settings.value("password", QString("")).toString());

	line4->addWidget(lblPassword);
	line4->addWidget(m_lePassword);

	QHBoxLayout *line5 = new QHBoxLayout();
	m_btnPoll = new QMaemo5ValueButton("Poll Interval");
	QStringList poll_values;
	poll_values << "2 min" << "5 min" << "10 min" << "15 min" << "30 min" << "1 hr";
	QStringListModel *lm = new QStringListModel(poll_values);
	QMaemo5ListPickSelector *lps = new QMaemo5ListPickSelector();
	lps->setModel(lm);
	m_btnPoll->setPickSelector(lps);
	m_btnPoll->setValueText(settings.value("poll_interval", QString("2 min")).toString());
	line5->addWidget(m_btnPoll);
	col1->addLayout(line5);

	QHBoxLayout *line6 = new QHBoxLayout();
	m_cbManualDismiss = new QCheckBox("Manually Dismiss Messages");
	if (settings.value("manual_dismiss", false).toBool()) {
		m_cbManualDismiss->setCheckState(Qt::Checked);
	} else {
		m_cbManualDismiss->setCheckState(Qt::Unchecked);
	}
	line6->addWidget(m_cbManualDismiss);
	col1->addLayout(line6);

	col1->addLayout(line3);
	col1->addLayout(line4);

	QVBoxLayout *col2 = new QVBoxLayout();
	QPushButton *btnSave = new QPushButton("Save");
	connect(btnSave, SIGNAL(clicked()), this, SLOT(save()));
	col2->addWidget(btnSave);
	col2->addStretch();

	layout->addLayout(col1);
	layout->addLayout(col2);

	QWidget *w = new QWidget(this);
	w->setLayout(layout);
	w->setMinimumSize(size().width(), size().height() - 100);
	scroll->setWidget(w);

	QVBoxLayout *l = new QVBoxLayout();
	l->addWidget(scroll);
	setLayout(l);
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
	settings.setValue("poll_interval", m_btnPoll->valueText());
	settings.setValue("manual_dismiss", m_cbManualDismiss->checkState() == Qt::Checked);
	settings.sync();
	emit accept();
}

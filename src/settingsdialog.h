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

#ifndef DARMA_MAEMO_SETTINGS_DIALOG_H
#define DARMA_MAEMO_SETTINGS_DIALOG_H

#include <QDialog>

#include <QLineEdit>
#include <QCheckBox>
#include <QMaemo5ValueButton>

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
	public:
		SettingsDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~SettingsDialog();
	
	public slots:
		void save();

	protected:
		void createControls();
	
		QLineEdit *m_leNickname;
		QLineEdit *m_leServerAddress;
		QLineEdit *m_leUsername;
		QLineEdit *m_lePassword;
		QCheckBox *m_cbManualDismiss;
		QMaemo5ValueButton *m_btnPoll;
};

#endif // DARMA_MAEMO_SETTINGS_DIALOG_H

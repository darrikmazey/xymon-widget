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

#ifndef DARMA_MAEMO_XYMON_WIDGET_H
#define DARMA_MAEMO_XYMON_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QNetworkReply>
#include <QTimer>
#include <QMouseEvent>
#include <QMaemo5InformationBox>

class XymonWidget : public QWidget
{
	Q_OBJECT
	
	public:
		XymonWidget(QWidget *parent = 0);
		~XymonWidget();
	
	public slots:
		void showSettingsDialog();
		void haveReply(QNetworkReply *reply);
		void reloadStatus();
		void homeScreenChanged(bool active);

	protected:
		void reload();
		void needsReconfigured();
		int pollIntervalTextToSeconds(const QString &txt);
		void mouseReleaseEvent(QMouseEvent *event);
		void touchLastUpdated();
		QString lastUpdated();
		void info(const QString &msg, int timeout = QMaemo5InformationBox::DefaultTimeout);

		QString m_serverAddress;
		QString m_nickname;
		QLabel *m_label;
		QLabel *m_colorLabel;
		QTimer *m_timer;
		QString m_currentColor;
		QString m_lastMessage;
		int m_consecutiveTimeouts;
		bool m_onScreen;
};

#endif // DARMA_MAEMO_XYMON_WIDGET_H

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

#include "qmaemo5homescreenadaptor.h"

#include <QtDebug>

#include <QApplication>
#include "xymonwidget.h"
#include <QFile>
#include <QString>
#include <QRegExp>
#include <QSettings>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	app.setApplicationName("xymon_widget");
	app.setOrganizationName("DarmaSoft, LLC.");
	app.setOrganizationDomain("darmasoft.com");

	XymonWidget *w = new XymonWidget();
	QMaemo5HomescreenAdaptor *adaptor = new QMaemo5HomescreenAdaptor(w);

	adaptor->setSettingsAvailable(true);
	QObject::connect(adaptor, SIGNAL(settingsRequested()), w, SLOT(showSettingsDialog()));
	QObject::connect(adaptor, SIGNAL(homescreenChanged(bool)), w, SLOT(homeScreenChanged(bool)));


	w->show();
	
	QSettings settings;
	if (!settings.value("first_time_configured").toBool() || settings.value("needs_reconfigured").toBool()) {
		w->showSettingsDialog();
	}

	int ret = app.exec();
	delete(adaptor);
	delete(w);

	return(ret);
}

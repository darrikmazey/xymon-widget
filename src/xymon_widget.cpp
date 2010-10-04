
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

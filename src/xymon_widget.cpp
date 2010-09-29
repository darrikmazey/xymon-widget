
#include "qmaemo5homescreenadaptor.h"

#include <QApplication>
#include "xymonwidget.h"

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

	w->show();
	app.exec();
}

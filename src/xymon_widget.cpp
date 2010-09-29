
#include "qmaemo5homescreenadaptor.h"

#include <QApplication>
#include "xymonwidget.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	XymonWidget *w = new XymonWidget();
	QMaemo5HomescreenAdaptor *adaptor = new QMaemo5HomescreenAdaptor(w);

	adaptor->setSettingsAvailable(true);
	QObject::connect(adaptor, SIGNAL(settingsRequested()), w, SLOT(showSettingsDialog()));

	w->show();
	app.exec();
}

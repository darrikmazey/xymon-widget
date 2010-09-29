
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

	/*
	QFile f("bb2.html");
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		exit(0);
	}

	QString data = f.readAll();

	QRegExp re(".*BODY BGCOLOR=\"(\\w+)\".*");
	if (re.exactMatch(data)) {
		qDebug() << QString("match!");
		qDebug() << re.captureCount();
		qDebug() << re.capturedTexts();
	} else {
		qDebug() << QString("no match!");
	}
	
	exit(0);
	*/

	XymonWidget *w = new XymonWidget();
	QMaemo5HomescreenAdaptor *adaptor = new QMaemo5HomescreenAdaptor(w);

	adaptor->setSettingsAvailable(true);
	QObject::connect(adaptor, SIGNAL(settingsRequested()), w, SLOT(showSettingsDialog()));

	w->show();
	
	QSettings settings;
	if (!settings.value("first_time_configured").toBool()) {
		w->showSettingsDialog();
	}

	app.exec();
}

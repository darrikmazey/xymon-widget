
#include "qmaemo5homescreenadaptor.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QLabel *lbl = new QLabel("test widget");
	QMaemo5HomescreenAdaptor *adaptor = new QMaemo5HomescreenAdaptor(lbl);

	lbl->show();
	app.exec();
}

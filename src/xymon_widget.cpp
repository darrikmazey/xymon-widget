
#include <QtDebug>
#include "application.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
	Application *app = new Application("xymon", "0.2", argc, argv);

	MainWindow *mw = new MainWindow();
	mw->show();

	return(app->exec());
}

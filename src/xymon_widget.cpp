
#include <QtDebug>
#include <QApplication>
#include <QLabel>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QLabel *lbl = new QLabel(QString("hello world!"));
	lbl->show();
	return(app.exec());
}

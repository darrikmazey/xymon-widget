
#include <QtDebug>

#include "application.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setWindowTitle(QString("%1 %2").arg(dApp->applicationName()).arg(dApp->appVersion()));
	qDebug() << QString("MainWindow::MainWindow()");
	QAction *actSettings = menuBar()->addAction(tr("Settings"));
	connect(actSettings, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
}

MainWindow::~MainWindow()
{
	qDebug() << QString("MainWindow::~MainWindow()");
}

void MainWindow::showSettingsDialog()
{
	qDebug() << QString("MainWindow::showSettingsDialog()");
	SettingsDialog s;
	int ret = s.exec();
	qDebug() << QString("dialog returned %1").arg(ret);
}


#ifndef DARMA_MAEMO_MAINWINDOW_H
#define DARMA_MAEMO_MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = 0);
		~MainWindow();

	public slots:
		void showSettingsDialog();
	
};
#endif // DARMA_MAEMO_MAINWINDOW_H


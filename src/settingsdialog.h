
#ifndef DARMA_MAEMO_SETTINGS_DIALOG_H
#define DARMA_MAEMO_SETTINGS_DIALOG_H

#include <QDialog>

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
	public:
		SettingsDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~SettingsDialog();
};

#endif // DARMA_MAEMO_SETTINGS_DIALOG_H

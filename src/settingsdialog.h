
#ifndef DARMA_MAEMO_SETTINGS_DIALOG_H
#define DARMA_MAEMO_SETTINGS_DIALOG_H

#include <QDialog>

#include <QLineEdit>

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
	public:
		SettingsDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
		~SettingsDialog();
	
	public slots:
		void save();

	protected:
		void createControls();
	
		QLineEdit *m_leNickname;
		QLineEdit *m_leServerAddress;
};

#endif // DARMA_MAEMO_SETTINGS_DIALOG_H

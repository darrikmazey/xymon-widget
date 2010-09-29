
#ifndef DARMA_MAEMO_XYMON_WIDGET_H
#define DARMA_MAEMO_XYMON_WIDGET_H

#include <QWidget>
#include <QLabel>

class XymonWidget : public QWidget
{
	Q_OBJECT
	
	public:
		XymonWidget(QWidget *parent = 0);
		~XymonWidget();
	
	public slots:
		void showSettingsDialog();

	protected:
		void reload();

		QString m_serverAddress;
		QString m_nickname;
		QLabel *m_label;
};

#endif // DARMA_MAEMO_XYMON_WIDGET_H

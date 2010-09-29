
#ifndef DARMA_MAEMO_XYMON_WIDGET_H
#define DARMA_MAEMO_XYMON_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QNetworkReply>

class XymonWidget : public QWidget
{
	Q_OBJECT
	
	public:
		XymonWidget(QWidget *parent = 0);
		~XymonWidget();
	
	public slots:
		void showSettingsDialog();
		void haveReply(QNetworkReply *reply);

	protected:
		void reload();
		void reloadStatus();

		QString m_serverAddress;
		QString m_nickname;
		QLabel *m_label;
};

#endif // DARMA_MAEMO_XYMON_WIDGET_H

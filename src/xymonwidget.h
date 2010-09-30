
#ifndef DARMA_MAEMO_XYMON_WIDGET_H
#define DARMA_MAEMO_XYMON_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QNetworkReply>
#include <QTimer>

class XymonWidget : public QWidget
{
	Q_OBJECT
	
	public:
		XymonWidget(QWidget *parent = 0);
		~XymonWidget();
	
	public slots:
		void showSettingsDialog();
		void haveReply(QNetworkReply *reply);
		void reloadStatus();

	protected:
		void reload();
		void needsReconfigured();
		int pollIntervalTextToSeconds(const QString &txt);

		QString m_serverAddress;
		QString m_nickname;
		QLabel *m_label;
		QLabel *m_colorLabel;
		QTimer *m_timer;
};

#endif // DARMA_MAEMO_XYMON_WIDGET_H

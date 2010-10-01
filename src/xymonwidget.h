
#ifndef DARMA_MAEMO_XYMON_WIDGET_H
#define DARMA_MAEMO_XYMON_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QNetworkReply>
#include <QTimer>
#include <QMouseEvent>
#include <QDateTime>

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
		void mouseReleaseEvent(QMouseEvent *event);

		QString m_serverAddress;
		QString m_nickname;
		QLabel *m_label;
		QLabel *m_colorLabel;
		QTimer *m_timer;
		QString m_currentColor;
		QString m_lastMessage;
		int m_consecutiveTimeouts;
		QDateTime m_lastUpdated;
		bool m_updated;
};

#endif // DARMA_MAEMO_XYMON_WIDGET_H

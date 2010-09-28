
#ifndef DARMA_MAEMO_APPLICATION_H
#define DARMA_MAEMO_APPLICATION_H

#include <QApplication>

#define dApp ((Application *) qApp)

class Application : public QApplication
{
	Q_OBJECT

	public:
		Application(const QString &appName, const QString &appVersion, int &argc, char **argv);
		~Application();

		QString appVersion() const;
		QString serverAddress() const;
		void setServerAddress(const QString &add);
	
	protected:
		QString m_appVersion;
		QString m_serverAddress;
};

#endif // DARMA_MAEMO_APPLICATION_H

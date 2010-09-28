
#include <QtDebug>

#include "application.h"

Application::Application(const QString &appName, const QString &appVersion, int &argc, char **argv) :
	QApplication(argc, argv)
{
	qDebug() << QString("Application::Application(%1, %2)").arg(appName).arg(appVersion);

	m_appVersion = appVersion;
	setApplicationName(appName);
	setOrganizationName(QString("DarmaSoft, LLC."));
	setOrganizationDomain(QString("darmasoft.com"));
	m_serverAddress = "";
}

Application::~Application()
{
	qDebug() << QString("Application::~Application()");
}

QString Application::appVersion() const
{
	return(m_appVersion);
}

QString Application::serverAddress() const
{
	return(m_serverAddress);
}

void Application::setServerAddress(const QString &add)
{
	m_serverAddress = add;
}

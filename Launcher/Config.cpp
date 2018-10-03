#include "Config.hpp"

#include <fstream>

#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QStringList>

#include "PatchInfo.hpp"

namespace Config
{
  const int g_launchVersion = 17;

  QVariant getLaunchSetting(const QString& setting, const QVariant &default_value)
  {
    qDebug() << "CurrentDir:" << QDir::current();
    QSettings m_pLaunchSettings(QDir::current().filePath("Launch.ini"), QSettings::IniFormat);

    return m_pLaunchSettings.value("Launch/" + setting, default_value);
  }

  QString getClientVersion()
  {
    QFile clientVersionFile(QDir::current().filePath("(version)"));
    if (!clientVersionFile.open(QIODevice::ReadOnly))
    {
      qDebug() << "Error open Client.version";
      return QString();
    }

    QString v = QTextStream(&clientVersionFile).readLine();

    clientVersionFile.close();

    return v.split('|').first().trimmed();
  }

  bool isLatestClientVersion()
  {
    return PatchInfo::getInstance().getLatestVersion() == Config::getClientVersion();
  }

  int getLaunchLatestVersion()
  {
    return PatchInfo::getInstance().getLaunchObject().value("LatestVersion").toInt();
  }

  QUrl getLaunchNewVersionUrl()
  {
    return PatchInfo::getInstance().getLaunchObject().value("NewVersionUrl").toString();
  }
}

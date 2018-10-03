#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QVariant>

namespace Config
{
  extern const int g_launchVersion;

  QVariant getLaunchSetting(const QString& setting, const QVariant& default_value = QVariant());
  QString getClientVersion();
  bool isLatestClientVersion();
  int getLaunchLatestVersion();
  QUrl getLaunchNewVersionUrl();
}

#endif // CONFIG_HPP

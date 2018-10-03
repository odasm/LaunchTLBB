#include "PatchInfo.hpp"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QUrl>

#include <QDebug>

#include "Config.hpp"

PatchInfo::PatchInfo()
{
  if (!this->load())
  {
    qDebug() << "Error when load PatchInfo.json";
  }
}

bool PatchInfo::load()
{
  QFile jsonFile("Patch/PatchInfo.json");
  if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QJsonDocument dataDocument;

    m_data = dataDocument.fromJson(QString(jsonFile.readAll()).toUtf8()).object();
  }
  else
  {
    qDebug() << "Error open PatchInfo";
  }

  jsonFile.close();

  return !m_data.isEmpty();
}

PatchInfo& PatchInfo::getInstance()
{
  static PatchInfo s_instance;

  return s_instance;
}

QString PatchInfo::getLatestVersion() const
{
  return m_data.value("LatestVersion").toString();
}

QJsonArray PatchInfo::getPatches() const
{
  return m_data.value("Patches").toArray();
}

int PatchInfo::getIndexOfPatch(const QString& versionType, const QString& version) const
{
  const auto &p = this->getPatches();
  int index = p.size();

  for (int i = 0; i < p.size(); i++)
  {
    if (p.at(i).toObject().value(versionType).toString() == version)
    {
      index = i;
      break;
    }
  }

  return index;
}

QVector<QUrl>& PatchInfo::getNewVersionList() const
{
  static QVector<QUrl> urlList;

  if (urlList.isEmpty())
  {
    QString versionFrom = Config::getClientVersion();
    int index;

    while (true)
    {
      index = this->getIndexOfPatch("VersionFrom", versionFrom);
      if (index >= this->getPatches().size())
      {
        break;
      }

      const auto &found = this->getPatches().at(index);
      versionFrom = found.toObject().value("VersionTo").toString();
      QUrl url = found.toObject().value("Url").toString();

      if (url.isEmpty() || versionFrom.isEmpty())
      {
        break;
      }

      urlList.push_back(url);

      if (versionFrom == this->getLatestVersion())
      {
        break;
      }
    }
  }

  return urlList;
}

QJsonObject PatchInfo::getLaunchObject() const
{
  return m_data.value("Launch").toObject();
}

QUrl PatchInfo::getLoginServerUrl() const
{
  return m_data.value("LoginServerUrl").toString();
}

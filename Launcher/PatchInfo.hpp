#ifndef PATCHINFO_HPP
#define PATCHINFO_HPP

#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QUrl>

class PatchInfo final
{
  private:
    PatchInfo();

  public:
    bool load();

  public:
    static PatchInfo& getInstance();
    QString getLatestVersion() const;
    QJsonArray getPatches() const;
    QVector<QUrl>& getNewVersionList() const;

    /**
     * @brief getIndexOfPatch
     * @param versionType
     * @param version
     * @return
     */
    int getIndexOfPatch(const QString& versionType, const QString& version) const;
    bool getIsLatest() const;
    std::size_t getDownloadLeft();
    QJsonObject getLaunchObject() const;
	QUrl getLoginServerUrl() const;

  private:
    QJsonObject m_data;
    bool m_isLatest;
};

#endif // PATCHINFO_HPP

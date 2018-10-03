#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <QString>
#include <QUrl>

namespace Utils
{
  QString basename(const QUrl& fullFilePath);

  QString humanSize(const qint64 realSize);

  QString getFileSHA256(const QString& fileName);

  void killProcess(const QString& processName);

  QString getSystemDir();

  QByteArray fileGetContent();

  bool isElevated();
}

#endif // HELPERS_HPP

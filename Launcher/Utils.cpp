#include "Utils.hpp"

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QFile>

#include <ShlObj.h>
#include <TlHelp32.h>
#include <Windows.h>

namespace Utils
{
  QString basename(const QUrl& fullFilePath)
  {
    return fullFilePath.fileName();
  }

  QString humanSize(const qint64 realSize)
  {
    auto size = static_cast<float>(realSize);

    static QStringList sizeList{
      "KB", "MB", "GB", "TB"
    };

    static QString unit("B");

    for (const auto& sizeText : sizeList)
    {
      unit = sizeText;
      if ((size /= 1024.f) < 1024.f)
      {
        break;
      }
    }

    return QString().setNum(size, 'f', 2) + unit;
  }

  QString getFileSHA256(const QString& fileName)
  {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
      return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);
    if (!hash.addData(&file))
    {
      return QString();
    }
    return hash.result().toHex().toUpper();
  }

  void killProcess(const QString& processName)
  {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
      if (processName.toStdWString() == pEntry.szExeFile)
      {
        HANDLE hProcess = OpenProcess(
          PROCESS_TERMINATE, 0,
          static_cast<DWORD>(pEntry.th32ProcessID)
          );
        if (hProcess && (pEntry.th32ProcessID != ::GetCurrentProcessId()))
        {
          qDebug() << "Killing:" << processName;
          TerminateProcess(hProcess, 9);
          CloseHandle(hProcess);
        }
      }
      hRes = ::Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
  }

  QString getSystemDir()
  {
    char lpBuffer[MAX_PATH];
    ::SHGetSpecialFolderPathA(nullptr, lpBuffer, CSIDL_SYSTEMX86, false);
    return lpBuffer;
  }

  bool isElevated()
  {
    bool fRet = false;
    HANDLE hToken = nullptr;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
      TOKEN_ELEVATION Elevation;
      DWORD cbSize = sizeof( TOKEN_ELEVATION );
      if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
        fRet = static_cast<bool>(Elevation.TokenIsElevated);
      }
    }
    if( hToken ) {
      CloseHandle( hToken );
    }
    return fRet;
  }
}

#include "PlayGamePushButton.hpp"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QStyle>
#include <QWindow>

#include <QDebug>

#include "Config.hpp"
#include "Utils.hpp"
#include "UtilsEE.hpp"

PlayGamePushButton::PlayGamePushButton(QWidget *parent) : QPushButton(parent)
{
  //this->resize(parent->size());
  qDebug() << "PlayButton size:" << this->size();

  connect(this, &QPushButton::clicked, [&](){
    if (!m_isClickAble)
    {
      return;
    }
    auto execAppFileName = Config::getLaunchSetting("GameExe").toString();
    QDir dir(QDir::currentPath());

    QFile file(dir.filePath(execAppFileName));
    if (!file.exists())
    {
      QMessageBox::warning(this, "Error", "File not exists: " + execAppFileName);
      return;
    }

    dir.setPath(dir.filePath(execAppFileName));
    dir.cdUp();

    QProcess::startDetached(
      file.fileName(), { "-fl" }, dir.path(), nullptr
      );

    QApplication::activeWindow()->hide();
    UtilsEE::onStartButtonClicked();
  });

  this->setIsClickAble(false);
  
}

void PlayGamePushButton::setIsClickAble(bool isClickAble)
{
  m_isClickAble = isClickAble;

  // Reset Attr
  this->setProperty("isClickAble", m_isClickAble);
  this->style()->unpolish(this);
  this->style()->polish(this);
}

#include "MinimizeAppPushButton.hpp"

#include <QMainWindow>

MinimizeAppPushButton::MinimizeAppPushButton(QWidget *parent) : QPushButton(parent)
{
  connect(this, &QPushButton::clicked, [parent](){
    static auto mainWindow = dynamic_cast<QMainWindow*>(parent->parent());
    mainWindow->setWindowState(mainWindow->windowState() | Qt::WindowMinimized);
  });
}

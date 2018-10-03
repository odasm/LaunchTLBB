#include "QuitAppPushButton.hpp"

#include <QApplication>

QuitAppPushButton::QuitAppPushButton(QWidget *parent) : QPushButton(parent)
{
  connect(this, &QPushButton::clicked, [](){
    qApp->quit();
  });
}

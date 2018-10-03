#include "MainWindow.hpp"

#include <QApplication>

#ifndef QT_DEBUG
#  include "InitCopyApp.hpp"
#endif

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

#ifndef QT_DEBUG
  InitCopyApp();
#endif

  MainWindow w;
  w.show();

  return a.exec();
}

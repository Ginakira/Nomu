#include <QApplication>
#include <QVersionNumber>

#include "src/main_window.h"
#include "version.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QVersionNumber version(MAJOR_VERSION, MINOR_VERSION);
  QApplication::setApplicationVersion(version.toString());
  MainWindow w;
  w.setWindowTitle(QString("%1 v%2").arg(APPLICATION_NAME, version.toString()));
  w.show();
  qDebug() << APPLICATION_NAME << version.toString() << "build" << BUILD_VERSION
           << "launched.";
  return QApplication::exec();
}

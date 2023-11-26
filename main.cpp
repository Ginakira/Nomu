#include <QApplication>
#include <QMessageBox>
#include <QSettings>

#include "src/main_window.h"
#include "version.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  auto version = Nomu::GetApplicationVersion();
  QApplication::setApplicationVersion(version.toString());

  const QString settings_file_name = "nomu.ini";
  QSettings settings(settings_file_name, QSettings::IniFormat);

  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    QMessageBox::warning(nullptr, "Oops",
                         "当前系统不支持托盘图标，程序即将退出。");
    return EXIT_FAILURE;
  }

  MainWindow w(settings);
  w.setWindowTitle(
      QString("%1 v%2").arg(Nomu::APPLICATION_NAME, version.toString()));
  w.show();
  qDebug() << Nomu::APPLICATION_NAME << version.toString() << "build"
           << Nomu::BUILD_VERSION << "launched.";

  QApplication::setQuitOnLastWindowClosed(false);

  return QApplication::exec();
}

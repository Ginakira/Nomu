#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QSettings &settings, QWidget *parent = nullptr);
  ~MainWindow() override;

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void IconActivated(QSystemTrayIcon::ActivationReason reason);
  void DrinkRecorded();
  void CountdownReset();
  void ChangeRemindImage();

 private:
  static constexpr int kTimerIntervalMs = 1000 * 1;
  void CreateTrayIcon();
  void CreateActions();
  void SetImageLabel();

  void CreateTimer();
  void StartTimer();
  void StopTimer();
  void TimerTickHandle();
  void SwitchTimer();
  void LoadSettings();
  void SaveSettings();
  void RestoreInfoToUI();

  QAction *label_action_{};
  QAction *minimize_action_{};
  QAction *restore_action_{};
  QAction *quit_action_{};

  QTimer *timer_{};
  int cur_countdown_sec_{};

  Ui::MainWindow *ui_;
  QPixmap *reminder_image_{};
  QSystemTrayIcon *tray_icon_{};
  QMenu *tray_icon_menu_{};

  QSettings &settings_;
  int total_drink_times_{};
  int remind_interval_min_{};
  QString reminder_image_path_{};
};
#endif// MAINWINDOW_H

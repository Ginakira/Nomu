#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <atomic>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
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

  QAction *label_action_{};
  QAction *minimize_action_{};
  QAction *restore_action_{};
  QAction *quit_action_{};

  QTimer *timer_{};
  int cur_countdown_sec_{};
  int cur_drink_times_{};

  Ui::MainWindow *ui_;
  QPixmap *reminder_image_{};
  QSystemTrayIcon *tray_icon_{};
  QMenu *tray_icon_menu_{};
};
#endif// MAINWINDOW_H

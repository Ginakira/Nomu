#include "main_window.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QVersionNumber>

#include "../version.h"
#include "remind_dialog.h"
#include "ui/ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  CreateActions();
  CreateTrayIcon();
  SetImageLabel();
  CreateTimer();

  connect(ui_->drink_record_button, &QPushButton::clicked, this,
          &MainWindow::DrinkRecorded);
  connect(ui_->reset_timer_button, &QPushButton::clicked, this,
          &MainWindow::CountdownReset);
  connect(ui_->update_interval_button, &QPushButton::clicked, this,
          &MainWindow::CountdownReset);
  connect(ui_->change_image_button, &QPushButton::clicked, this,
          &MainWindow::ChangeRemindImage);
  connect(ui_->switch_timer_button, &QPushButton::clicked, this,
          &MainWindow::SwitchTimer);

  tray_icon_->show();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::CreateActions() {
  auto app_name = QString("%1 v%2").arg(
      Nomu::APPLICATION_NAME, Nomu::GetApplicationVersion().toString());
  label_action_ = new QAction(app_name);
  label_action_->setDisabled(true);

  minimize_action_ = new QAction("最小化", this);
  connect(minimize_action_, &QAction::triggered, this, &QWidget::hide);

  restore_action_ = new QAction("打开", this);
  connect(restore_action_, &QAction::triggered, this, &QWidget::show);

  quit_action_ = new QAction("退出", this);
  connect(quit_action_, &QAction::triggered, this, &QCoreApplication::exit);
}

void MainWindow::CreateTrayIcon() {
  tray_icon_menu_ = new QMenu(this);
  tray_icon_menu_->addAction(label_action_);
  tray_icon_menu_->addSeparator();
  tray_icon_menu_->addAction(minimize_action_);
  tray_icon_menu_->addAction(restore_action_);
  tray_icon_menu_->addSeparator();
  tray_icon_menu_->addAction(quit_action_);

  tray_icon_ = new QSystemTrayIcon(this);
  tray_icon_->setToolTip(Nomu::APPLICATION_NAME);
  tray_icon_->setIcon(QIcon(":/icon/nomu.ico"));
  tray_icon_->setContextMenu(tray_icon_menu_);

  connect(tray_icon_, &QSystemTrayIcon::activated, this,
          &MainWindow::IconActivated);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (!event->spontaneous() || !isVisible()) { return; }
  if (tray_icon_->isVisible()) {
    tray_icon_->showMessage("Nomu后台工作中", "守护最好的膀胱");
    hide();
    event->ignore();
  }
}
void MainWindow::IconActivated(QSystemTrayIcon::ActivationReason reason) {
  switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick: {
      show();
    } break;
    default: {
    } break;
  }
}

void MainWindow::SetImageLabel() {
  reminder_image_ = new QPixmap(":/icon/nomu.jpg");
  int w = ui_->image_label->width();
  ui_->image_label->setPixmap(
      reminder_image_->scaledToWidth(w, Qt::SmoothTransformation));
}

void MainWindow::CreateTimer() {
  CountdownReset();
  timer_ = new QTimer;
  StartTimer();
  connect(timer_, &QTimer::timeout, this, &MainWindow::TimerTickHandle);
}

void MainWindow::TimerTickHandle() {
  if (cur_countdown_sec_ > 0) {
    ui_->timer_lcd->display(cur_countdown_sec_--);
  } else {
    auto remind_dialog =
        new RemindDialog(this, reminder_image_, cur_drink_times_);
    connect(remind_dialog, &RemindDialog::DrinkConfirmed, this,
            &MainWindow::DrinkRecorded);
    remind_dialog->exec();
    delete remind_dialog;
    CountdownReset();
  }
}

void MainWindow::DrinkRecorded() {
  qDebug() << "Drink record, cur: " << cur_drink_times_;
  ++cur_drink_times_;
  ui_->drink_count_lcd->display(cur_drink_times_);
}

void MainWindow::CountdownReset() {
  cur_countdown_sec_ = ui_->interval_min_spin_box->value() * 60;
}
void MainWindow::ChangeRemindImage() {
  QMessageBox::warning(this, "在做了", "此功能需购买DLC");
}

void MainWindow::SwitchTimer() {
  if (!timer_) { return; }
  if (timer_->isActive()) {
    StopTimer();
    ui_->switch_timer_button->setText("恢复计时");
  } else {
    StartTimer();
    ui_->switch_timer_button->setText("暂停计时");
  }
}

void MainWindow::StartTimer() {
  if (!timer_) { return; }
  timer_->start(kTimerIntervalMs);
  qDebug() << "Timer active: " << timer_->isActive();
}

void MainWindow::StopTimer() {
  if (!timer_) { return; }
  timer_->stop();
  qDebug() << "Timer active: " << timer_->isActive();
}

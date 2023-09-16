#include "remind_dialog.h"

#include "ui/ui_remind_dialog.h"

RemindDialog::RemindDialog(QWidget *parent, QPixmap *pixmap,
                           int cur_drink_count)
    : QDialog(parent),
      ui_(new Ui::RemindDialog) {
  ui_->setupUi(this);

  ui_->image_label->setPixmap(
      pixmap->scaledToWidth(200, Qt::SmoothTransformation));
  ui_->drink_count_lcd_number->display(cur_drink_count + 1);

  connect(ui_->ok_button, &QPushButton::clicked, this, [this]() {
    emit DrinkConfirmed();
    close();
  });
  connect(ui_->cancel_button, &QPushButton::clicked, this,
          &RemindDialog::reject);
}

RemindDialog::~RemindDialog() { delete ui_; }

#ifndef REMIND_DIALOG_H
#define REMIND_DIALOG_H

#include <QDialog>

namespace Ui {
class RemindDialog;
}

class RemindDialog : public QDialog {
  Q_OBJECT

 public:
  explicit RemindDialog(QWidget *parent, QPixmap *pixmap, int cur_drink_count);
  ~RemindDialog() override;

 signals:
  void DrinkConfirmed();

 private:
  Ui::RemindDialog *ui_;
};

#endif// REMIND_DIALOG_H

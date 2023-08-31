#ifndef CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CREDIT_H_
#define CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CREDIT_H_

#include <QDialog>

#include "s21_calc_controller.h"

namespace Ui {
class S21Credit;
}

namespace s21 {

class S21Credit : public QDialog {
  Q_OBJECT

 public:
  explicit S21Credit(S21Controller *controller);
  ~S21Credit();

 private slots:
  void OnPushButtonCalcClicked();
  void OnComboBoxCurrentIndexChanged(int index);

 private:
  Ui::S21Credit *ui_;

  S21Controller *controller_;
};

}  // namespace s21

#endif  // CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CREDIT_H_

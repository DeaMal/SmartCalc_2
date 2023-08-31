#ifndef CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_DEPOSIT_H_
#define CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_DEPOSIT_H_

#include <QDialog>

#include "s21_calc_controller.h"

namespace Ui {
class S21Deposit;
}

namespace s21 {

class S21Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit S21Deposit(S21Controller *controller);
  ~S21Deposit();

 private slots:
  void OnPushButtonCalcClicked();
  void OnPushButtonPlusReplClicked();
  void OnPushButtonPlusWithdrawClicked();
  void OnPushButtonMinusReplClicked();
  void OnPushButtonMinusWithdrawClicked();
  void OnComboBoxCapitalCurrentIndexChanged(int index);
  void OnComboBoxAmountCurrentIndexChanged();
  void OnSpinBoxPeriodValueChanged(int arg1);
  void OnSpinBoxAmountValueChanged(int arg1);
  void OnSpinBoxRateValueChanged(double arg1);

 private:
  Ui::S21Deposit *ui_;

  S21Controller *controller_;
};

}  // namespace s21

#endif  // CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_DEPOSIT_H_

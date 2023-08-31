#ifndef CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_VIEWER_H_
#define CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_VIEWER_H_

#include <s21_calc_credit.h>
#include <s21_calc_deposit.h>

#include <QEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <QVector>

#include "s21_calc_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class S21Viewer;
}
QT_END_NAMESPACE

namespace s21 {

class S21Viewer : public QMainWindow {
  Q_OBJECT

 public:
  S21Viewer(S21Controller *controller);
  ~S21Viewer();

 private:
  Ui::S21Viewer *ui_;
  S21Controller *controller_;
  S21Credit credit_;
  S21Deposit deposit_;

 private slots:
  void DigitsNumbers();
  void InsertFunc();
  void InsertOperand();
  void OnPushButtonResClicked();
  void OnPushButtonClearFormulaClicked();
  void OnPushButtonClearResClicked();
  void OnPushButtonClearXClicked();
  void OnPushButtonPiClicked();
  void OnPushButtonEClicked();
  void OnPushButtonGraphClicked();
  void OnPushButtonCreditClicked();
  void OnPushButtonDepositClicked();
  void OnPushButtonToFormulaClicked();
  void DrawGraph(std::string &out_s);
  void CheckGraphX();
  int CheckGraphY();

 protected:
  virtual bool eventFilter(QObject *watched, QEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
};

}  // namespace s21

#endif  // CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_VIEWER_H_

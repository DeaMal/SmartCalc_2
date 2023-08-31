#include "s21_calc_credit.h"

#include "ui_s21_calc_credit.h"

namespace s21 {

S21Credit::S21Credit(S21Controller *controller)
    : QDialog(nullptr), ui_(new Ui::S21Credit), controller_(controller) {
  ui_->setupUi(this);

  connect(ui_->pushButton_Calc, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCalcClicked()));
  connect(
      ui_->comboBox,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21Credit::OnComboBoxCurrentIndexChanged);
}

S21Credit::~S21Credit() { delete ui_; }

void S21Credit::OnPushButtonCalcClicked() {
  ui_->lineEdit_Pay->clear();
  ui_->lineEdit_Over->clear();
  ui_->lineEdit_Total->clear();
  bool dif = ui_->radioButton_A->isChecked();
  int index = ui_->comboBox->currentIndex();
  double amount = ui_->spinBox_Amount->value();
  double term = ui_->spinBox_Term->value();
  double rate = ui_->spinBox_Rate->value() / 100.0;
  std::string pay = "", over = "", total = "";
  if (!controller_->GetCreditResult(dif, index, amount, term, rate, pay, over,
                                    total)) {
    ui_->lineEdit_Pay->setText(QString::fromStdString(pay));
    ui_->lineEdit_Over->setText(QString::fromStdString(over));
    ui_->lineEdit_Total->setText(QString::fromStdString(total));
  }
}

void S21Credit::OnComboBoxCurrentIndexChanged(int index) {
  if (index == 1) {
    ui_->label_Amount->setText("Amount of credit");
    ui_->spinBox_Amount->setValue(0);
    ui_->spinBox_Amount->setMaximum(100000000);
    ui_->label_Rub->setText("Rub");

    ui_->label_Term->setText("Monthly payment");
    ui_->spinBox_Term->setValue(0);
    ui_->spinBox_Term->setMaximum(100000000);
    ui_->label_Month->setText("Rub");

    ui_->label_Pay->setText("Credit term");
    ui_->label_Rub_2->setText("Month");

    ui_->lineEdit_Pay->clear();
    ui_->lineEdit_Over->clear();
    ui_->lineEdit_Total->clear();
    ui_->radioButton_A->setEnabled(false);
    ui_->radioButton_D->setEnabled(false);
  } else if (index == 0) {
    ui_->label_Amount->setText("Amount of credit");
    ui_->spinBox_Amount->setValue(0);
    ui_->spinBox_Amount->setMaximum(100000000);
    ui_->label_Rub->setText("Rub");

    ui_->label_Term->setText("Credit term");
    ui_->spinBox_Term->setValue(0);
    ui_->spinBox_Term->setMaximum(1200);
    ui_->label_Month->setText("Month");

    ui_->label_Pay->setText("Monthly payment");
    ui_->label_Rub_2->setText("Rub");

    ui_->lineEdit_Pay->clear();
    ui_->lineEdit_Over->clear();
    ui_->lineEdit_Total->clear();
    ui_->radioButton_A->setEnabled(true);
    ui_->radioButton_D->setEnabled(true);
  } else {
    ui_->label_Amount->setText("Monthly payment");
    ui_->spinBox_Amount->setValue(0);
    ui_->spinBox_Amount->setMaximum(100000000);
    ui_->label_Rub->setText("Rub");

    ui_->label_Term->setText("Credit term");
    ui_->spinBox_Term->setValue(0);
    ui_->spinBox_Term->setMaximum(1200);
    ui_->label_Month->setText("Month");

    ui_->label_Pay->setText("Amount of credit");
    ui_->label_Rub_2->setText("Rub");

    ui_->lineEdit_Pay->clear();
    ui_->lineEdit_Over->clear();
    ui_->lineEdit_Total->clear();
    ui_->radioButton_A->setEnabled(false);
    ui_->radioButton_D->setEnabled(false);
  }
}

}  // namespace s21

#include "s21_calc_deposit.h"

#include "ui_s21_calc_deposit.h"

namespace s21 {

S21Deposit::S21Deposit(S21Controller *controller)
    : QDialog(nullptr), ui_(new Ui::S21Deposit), controller_(controller) {
  ui_->setupUi(this);
  ui_->spinBox_amount->setFocus();

  connect(ui_->pushButton_calc, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCalcClicked()));
  connect(ui_->pushButton_plus_repl, SIGNAL(clicked()), this,
          SLOT(OnPushButtonPlusReplClicked()));
  connect(ui_->pushButton_plus_withdraw, SIGNAL(clicked()), this,
          SLOT(OnPushButtonPlusWithdrawClicked()));
  connect(ui_->pushButton_minus_repl, SIGNAL(clicked()), this,
          SLOT(OnPushButtonMinusReplClicked()));
  connect(ui_->pushButton_minus_withdraw, SIGNAL(clicked()), this,
          SLOT(OnPushButtonMinusWithdrawClicked()));

  connect(
      ui_->comboBox_capital,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21Deposit::OnComboBoxCapitalCurrentIndexChanged);
  connect(
      ui_->comboBox_amount,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21Deposit::OnComboBoxAmountCurrentIndexChanged);

  connect(ui_->spinBox_period,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &S21Deposit::OnSpinBoxPeriodValueChanged);
  connect(ui_->spinBox_amount,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &S21Deposit::OnSpinBoxAmountValueChanged);
  connect(ui_->spinBox_rate,
          static_cast<void (QDoubleSpinBox::*)(double)>(
              &QDoubleSpinBox::valueChanged),
          this, &S21Deposit::OnSpinBoxRateValueChanged);
}

S21Deposit::~S21Deposit() { delete ui_; }

void S21Deposit::OnSpinBoxPeriodValueChanged(int arg1) {
  int rowCountRepl = ui_->tableWidget_repl->rowCount();
  if (ui_->tableWidget_repl->item(0, 0)->text() != "None") {
    for (int k = 0; k < rowCountRepl; k++) {
      if (ui_->tableWidget_repl->item(k, 1)->text().toInt() > 4 + arg1) {
        if (k == 0 && rowCountRepl == 1) {
          ui_->tableWidget_repl->clear();
          ui_->tableWidget_repl->setColumnWidth(0, 70);
          ui_->tableWidget_repl->setColumnWidth(1, 70);
          ui_->tableWidget_repl->setColumnWidth(2, 70);
          ui_->tableWidget_repl->setColumnWidth(3, 65);
          ui_->tableWidget_repl->setShowGrid(false);
          ui_->tableWidget_repl->setItem(0, 0, new QTableWidgetItem("None"));
        } else {
          ui_->tableWidget_repl->removeRow(k);
          k = -1;
          rowCountRepl = ui_->tableWidget_repl->rowCount();
          for (int l = 0; l < rowCountRepl; l++) {
            ui_->tableWidget_repl->setItem(
                l, 0, new QTableWidgetItem(QString::number(l + 1)));
          }
        }
      }
    }
  }
  int rowCountWith = ui_->tableWidget_withdraw->rowCount();
  if (ui_->tableWidget_withdraw->item(0, 0)->text() != "None") {
    for (int k = 0; k < rowCountWith; k++) {
      if (ui_->tableWidget_withdraw->item(k, 1)->text().toInt() > 4 + arg1) {
        if (k == 0 && rowCountWith == 1) {
          ui_->tableWidget_withdraw->clear();
          ui_->tableWidget_withdraw->setColumnWidth(0, 70);
          ui_->tableWidget_withdraw->setColumnWidth(1, 70);
          ui_->tableWidget_withdraw->setColumnWidth(2, 70);
          ui_->tableWidget_withdraw->setColumnWidth(3, 65);
          ui_->tableWidget_withdraw->setShowGrid(false);
          ui_->tableWidget_withdraw->setItem(0, 0,
                                             new QTableWidgetItem("None"));
        } else {
          ui_->tableWidget_withdraw->removeRow(k);
          k = -1;
          rowCountWith = ui_->tableWidget_withdraw->rowCount();
          for (int l = 0; l < rowCountWith; l++) {
            ui_->tableWidget_withdraw->setItem(
                l, 0, new QTableWidgetItem(QString::number(l + 1)));
          }
        }
      }
    }
  }
  if (arg1 > 0) {
    ui_->label_replen->setEnabled(true);
    ui_->tableWidget_repl->setEnabled(true);
    ui_->pushButton_minus_repl->setEnabled(true);

    if (ui_->spinBox_amount->value() && ui_->spinBox_rate->value()) {
      ui_->pushButton_calc->setEnabled(true);
    }

    ui_->comboBox_new_repl->clear();
    ui_->comboBox_new_repl->addItem("Once a month");
    ui_->comboBox_new_repl->addItem("Once every 2 months");
    ui_->comboBox_new_repl->addItem("Once a quarter");
    ui_->comboBox_new_repl->addItem("Semiannually");
    ui_->comboBox_new_repl->addItem("Once a year");
    int i = 0;
    while (i < arg1) {
      ui_->comboBox_new_repl->addItem("One-time " + QString::number(i + 1) +
                                      " month");
      i++;
    }
    ui_->comboBox_new_repl->setEnabled(true);
    ui_->spinBox_new_repl->setEnabled(true);
    ui_->pushButton_plus_repl->setEnabled(true);

    ui_->label_withdraw->setEnabled(true);
    ui_->tableWidget_withdraw->setEnabled(true);
    ui_->pushButton_minus_withdraw->setEnabled(true);
    ui_->comboBox_new_withdraw->clear();
    ui_->comboBox_new_withdraw->addItem("Once a month");
    ui_->comboBox_new_withdraw->addItem("Once every 2 months");
    ui_->comboBox_new_withdraw->addItem("Once a quarter");
    ui_->comboBox_new_withdraw->addItem("Semiannually");
    ui_->comboBox_new_withdraw->addItem("Once a year");
    i = 0;
    while (i < arg1) {
      ui_->comboBox_new_withdraw->addItem("One-time " + QString::number(i + 1) +
                                          " month");
      i++;
    }
    ui_->comboBox_new_withdraw->setEnabled(true);
    ui_->spinBox_new_withdraw->setEnabled(true);
    ui_->pushButton_plus_withdraw->setEnabled(true);
  } else {
    ui_->label_replen->setEnabled(false);
    ui_->tableWidget_repl->setEnabled(false);
    ui_->pushButton_minus_repl->setEnabled(false);
    ui_->comboBox_new_repl->setEnabled(false);
    ui_->spinBox_new_repl->setEnabled(false);
    ui_->pushButton_plus_repl->setEnabled(false);

    ui_->label_withdraw->setEnabled(false);
    ui_->tableWidget_withdraw->setEnabled(false);
    ui_->pushButton_minus_withdraw->setEnabled(false);
    ui_->comboBox_new_withdraw->setEnabled(false);
    ui_->spinBox_new_withdraw->setEnabled(false);
    ui_->pushButton_plus_withdraw->setEnabled(false);

    ui_->pushButton_calc->setEnabled(false);
  }
}

void S21Deposit::OnPushButtonCalcClicked() {
  ui_->lineEdit_charge->clear();
  ui_->lineEdit_tex_amount->clear();
  ui_->lineEdit_total->clear();
  double amount = ui_->spinBox_amount->value();
  double period = ui_->spinBox_period->value();
  double rate = ui_->spinBox_rate->value();
  double tax = ui_->spinBox_tax->value();
  int freq_index = ui_->comboBox_freq->currentIndex();
  std::string charge = "", tax_amount = "", total = "";
  int rowCountRepl = 0, rowCountWith = 0;
  if (ui_->tableWidget_repl->item(0, 0)->text() != "None") {
    rowCountRepl = ui_->tableWidget_repl->rowCount();
  }
  double arr_repl[rowCountRepl + 1][2];
  for (int i = 0; i < rowCountRepl; ++i) {
    arr_repl[i][0] = ui_->tableWidget_repl->item(i, 1)->text().toDouble();
    arr_repl[i][1] = ui_->tableWidget_repl->item(i, 3)->text().toDouble();
  }
  if (ui_->tableWidget_withdraw->item(0, 0)->text() != "None") {
    rowCountWith = ui_->tableWidget_withdraw->rowCount();
  }
  double arr_with[rowCountWith + 1][2];
  for (int i = 0; i < rowCountWith; ++i) {
    arr_with[i][0] = ui_->tableWidget_withdraw->item(i, 1)->text().toDouble();
    arr_with[i][1] = ui_->tableWidget_withdraw->item(i, 3)->text().toDouble();
  }
  if (!controller_->GetDepositResult(amount, period, rate, tax, freq_index,
                                     rowCountRepl, rowCountWith, arr_repl,
                                     arr_with, charge, tax_amount, total)) {
    ui_->lineEdit_charge->setText(QString::fromStdString(charge));
    ui_->lineEdit_tex_amount->setText(QString::fromStdString(tax_amount));
    ui_->lineEdit_total->setText(QString::fromStdString(total));
  }
}

void S21Deposit::OnPushButtonPlusReplClicked() {
  int i = ui_->tableWidget_repl->rowCount();
  if (ui_->spinBox_new_repl->value() != 0 && i < 100) {
    if (ui_->tableWidget_repl->item(0, 0)->text() == "None") {
      ui_->tableWidget_repl->clear();
      ui_->tableWidget_repl->setColumnWidth(0, 20);
      ui_->tableWidget_repl->setColumnWidth(1, 0);
      ui_->tableWidget_repl->setColumnWidth(2, 150);
      ui_->tableWidget_repl->setColumnWidth(3, 105);
      ui_->tableWidget_repl->setShowGrid(true);
    } else {
      int find = 0;
      for (int k = 0; k < i; k++) {
        if (ui_->comboBox_new_repl->currentIndex() ==
            ui_->tableWidget_repl->item(k, 1)->text().toInt()) {
          i = k + 1;
          find++;
        }
      }
      if (!find) {
        ui_->tableWidget_repl->insertRow(i);
        i++;
      }
    }
    ui_->tableWidget_repl->setItem(i - 1, 0,
                                   new QTableWidgetItem(QString::number(i)));
    ui_->tableWidget_repl->item(i - 1, 0)->setFlags(
        ui_->tableWidget_repl->item(i - 1, 0)->flags() & ~Qt::ItemIsEditable);

    ui_->tableWidget_repl->setItem(
        i - 1, 1,
        new QTableWidgetItem(
            QString::number(ui_->comboBox_new_repl->currentIndex())));
    ui_->tableWidget_repl->item(i - 1, 1)->setFlags(
        ui_->tableWidget_repl->item(i - 1, 1)->flags() & ~Qt::ItemIsEditable);

    ui_->tableWidget_repl->setItem(
        i - 1, 2, new QTableWidgetItem(ui_->comboBox_new_repl->currentText()));
    ui_->tableWidget_repl->item(i - 1, 2)->setFlags(
        ui_->tableWidget_repl->item(i - 1, 2)->flags() & ~Qt::ItemIsEditable);

    ui_->tableWidget_repl->setItem(
        i - 1, 3,
        new QTableWidgetItem(
            QString::number(ui_->spinBox_new_repl->value(), 'f', 2)));
    ui_->tableWidget_repl->item(i - 1, 3)->setFlags(
        ui_->tableWidget_repl->item(i - 1, 3)->flags() & ~Qt::ItemIsEditable);

    QModelIndex index = ui_->tableWidget_repl->model()->index(i - 1, 3);
    ui_->tableWidget_repl->setCurrentIndex(index);
    ui_->tableWidget_repl->scrollTo(index);
  }
}

void S21Deposit::OnPushButtonPlusWithdrawClicked() {
  int i = ui_->tableWidget_withdraw->rowCount();
  if (ui_->spinBox_new_withdraw->value() != 0 && i < 100) {
    if (ui_->tableWidget_withdraw->item(0, 0)->text() == "None") {
      ui_->tableWidget_withdraw->clear();
      ui_->tableWidget_withdraw->setColumnWidth(0, 20);
      ui_->tableWidget_withdraw->setColumnWidth(1, 0);
      ui_->tableWidget_withdraw->setColumnWidth(2, 150);
      ui_->tableWidget_withdraw->setColumnWidth(3, 105);
      ui_->tableWidget_withdraw->setShowGrid(true);
    } else {
      int find = 0;
      for (int k = 0; k < i; k++) {
        if (ui_->comboBox_new_withdraw->currentIndex() ==
            ui_->tableWidget_withdraw->item(k, 1)->text().toInt()) {
          i = k + 1;
          find++;
        }
      }
      if (!find) {
        ui_->tableWidget_withdraw->insertRow(i);
        i++;
      }
    }
    ui_->tableWidget_withdraw->setItem(
        i - 1, 0, new QTableWidgetItem(QString::number(i)));
    ui_->tableWidget_withdraw->item(i - 1, 0)->setFlags(
        ui_->tableWidget_withdraw->item(i - 1, 0)->flags() &
        ~Qt::ItemIsEditable);

    ui_->tableWidget_withdraw->setItem(
        i - 1, 1,
        new QTableWidgetItem(
            QString::number(ui_->comboBox_new_withdraw->currentIndex())));
    ui_->tableWidget_withdraw->item(i - 1, 1)->setFlags(
        ui_->tableWidget_withdraw->item(i - 1, 1)->flags() &
        ~Qt::ItemIsEditable);

    ui_->tableWidget_withdraw->setItem(
        i - 1, 2,
        new QTableWidgetItem(ui_->comboBox_new_withdraw->currentText()));
    ui_->tableWidget_withdraw->item(i - 1, 2)->setFlags(
        ui_->tableWidget_withdraw->item(i - 1, 2)->flags() &
        ~Qt::ItemIsEditable);

    ui_->tableWidget_withdraw->setItem(
        i - 1, 3,
        new QTableWidgetItem(
            QString::number(ui_->spinBox_new_withdraw->value(), 'f', 2)));
    ui_->tableWidget_withdraw->item(i - 1, 3)->setFlags(
        ui_->tableWidget_withdraw->item(i - 1, 3)->flags() &
        ~Qt::ItemIsEditable);

    QModelIndex index = ui_->tableWidget_withdraw->model()->index(i - 1, 3);
    ui_->tableWidget_withdraw->setCurrentIndex(index);
    ui_->tableWidget_withdraw->scrollTo(index);
  }
}

void S21Deposit::OnPushButtonMinusReplClicked() {
  int rowCountRepl = ui_->tableWidget_repl->rowCount();
  if (ui_->tableWidget_repl->item(0, 0)->text() != "None") {
    int k = ui_->tableWidget_repl->currentItem()->row();
    if (k == 0 && rowCountRepl == 1) {
      ui_->tableWidget_repl->clear();
      ui_->tableWidget_repl->setColumnWidth(0, 70);
      ui_->tableWidget_repl->setColumnWidth(1, 70);
      ui_->tableWidget_repl->setColumnWidth(2, 70);
      ui_->tableWidget_repl->setColumnWidth(3, 65);
      ui_->tableWidget_repl->setShowGrid(false);
      ui_->tableWidget_repl->setItem(0, 0, new QTableWidgetItem("None"));
    } else {
      ui_->tableWidget_repl->removeRow(k);
      rowCountRepl = ui_->tableWidget_repl->rowCount();
      for (int l = 0; l < rowCountRepl; l++) {
        ui_->tableWidget_repl->setItem(
            l, 0, new QTableWidgetItem(QString::number(l + 1)));
      }
    }
  }
}

void S21Deposit::OnPushButtonMinusWithdrawClicked() {
  int rowCountWith = ui_->tableWidget_withdraw->rowCount();
  if (ui_->tableWidget_withdraw->item(0, 0)->text() != "None") {
    int k = ui_->tableWidget_withdraw->currentItem()->row();
    if (k == 0 && rowCountWith == 1) {
      ui_->tableWidget_withdraw->clear();
      ui_->tableWidget_withdraw->setColumnWidth(0, 70);
      ui_->tableWidget_withdraw->setColumnWidth(1, 70);
      ui_->tableWidget_withdraw->setColumnWidth(2, 70);
      ui_->tableWidget_withdraw->setColumnWidth(3, 65);
      ui_->tableWidget_withdraw->setShowGrid(false);
      ui_->tableWidget_withdraw->setItem(0, 0, new QTableWidgetItem("None"));
    } else {
      ui_->tableWidget_withdraw->removeRow(k);
      rowCountWith = ui_->tableWidget_withdraw->rowCount();
      for (int l = 0; l < rowCountWith; l++) {
        ui_->tableWidget_withdraw->setItem(
            l, 0, new QTableWidgetItem(QString::number(l + 1)));
      }
    }
  }
}

void S21Deposit::OnSpinBoxRateValueChanged(double arg1) {
  if (arg1 && ui_->spinBox_amount->value() && ui_->spinBox_period->value()) {
    ui_->pushButton_calc->setEnabled(true);
  } else {
    ui_->pushButton_calc->setEnabled(false);
  }
}

void S21Deposit::OnSpinBoxAmountValueChanged(int arg1) {
  if (arg1 && ui_->spinBox_rate->value() && ui_->spinBox_period->value()) {
    ui_->pushButton_calc->setEnabled(true);
  } else {
    ui_->pushButton_calc->setEnabled(false);
  }
}

void S21Deposit::OnComboBoxCapitalCurrentIndexChanged(int index) {
  if (index == 0) {
    ui_->comboBox_freq->setEnabled(true);
  } else {
    ui_->comboBox_freq->setCurrentIndex(6);
    ui_->comboBox_freq->setEnabled(false);
  }
}

void S21Deposit::OnComboBoxAmountCurrentIndexChanged() {
  ui_->label_charge_rub->setText(ui_->comboBox_amount->currentText());
  ui_->label_tex_amount_rub->setText(ui_->comboBox_amount->currentText());
  ui_->label_total_rub->setText(ui_->comboBox_amount->currentText());
}

}  // namespace s21

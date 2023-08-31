#include "s21_calc_viewer.h"

#include "ui_s21_calc_viewer.h"

namespace s21 {

S21Viewer::S21Viewer(S21Controller *controller)
    : QMainWindow(nullptr),
      ui_(new Ui::S21Viewer),
      controller_(controller),
      credit_(controller),
      deposit_(controller) {
  ui_->setupUi(this);
  ui_->textEdit_frml->installEventFilter(this);
  ui_->textEdit_frml->setFocus();

  connect(ui_->pushButton_res, SIGNAL(clicked()), this,
          SLOT(OnPushButtonResClicked()));
  connect(ui_->pushButton_clrfrml, SIGNAL(clicked()), this,
          SLOT(OnPushButtonClearFormulaClicked()));
  connect(ui_->pushButton_clrres, SIGNAL(clicked()), this,
          SLOT(OnPushButtonClearResClicked()));
  connect(ui_->pushButton_clrx, SIGNAL(clicked()), this,
          SLOT(OnPushButtonClearXClicked()));
  connect(ui_->pushButton_pi, SIGNAL(clicked()), this,
          SLOT(OnPushButtonPiClicked()));
  connect(ui_->pushButton_graph, SIGNAL(clicked()), this,
          SLOT(OnPushButtonGraphClicked()));
  connect(ui_->pushButton_credit, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCreditClicked()));
  connect(ui_->pushButton_deposit, SIGNAL(clicked()), this,
          SLOT(OnPushButtonDepositClicked()));
  connect(ui_->pushButton_e, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEClicked()));
  connect(ui_->pushButton_to_formula, SIGNAL(clicked()), this,
          SLOT(OnPushButtonToFormulaClicked()));

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));

  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(InsertOperand()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this, SLOT(InsertOperand()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(InsertOperand()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(InsertOperand()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(InsertOperand()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(InsertOperand()));
  connect(ui_->pushButton_opnbkt, SIGNAL(clicked()), this,
          SLOT(InsertOperand()));
  connect(ui_->pushButton_clsbkt, SIGNAL(clicked()), this,
          SLOT(InsertOperand()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(InsertOperand()));

  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(InsertFunc()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(InsertFunc()));
}

S21Viewer::~S21Viewer() { delete ui_; }

void S21Viewer::DigitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui_->lineEdit_x->hasFocus()) {
    ui_->lineEdit_x->insert(button->text());
  } else {
    ui_->textEdit_frml->insertPlainText(button->text());
    ui_->textEdit_frml->setFocus();
  }
}

void S21Viewer::InsertOperand() {
  QPushButton *button = (QPushButton *)sender();
  if (ui_->lineEdit_x->hasFocus()) {
  } else {
    ui_->textEdit_frml->insertPlainText(button->text());
    ui_->textEdit_frml->setFocus();
  }
}

void S21Viewer::InsertFunc() {
  QPushButton *button = (QPushButton *)sender();
  if (ui_->lineEdit_x->hasFocus()) {
  } else {
    ui_->textEdit_frml->insertPlainText(button->text() + "(");
    ui_->textEdit_frml->setFocus();
  }
}

void S21Viewer::OnPushButtonClearFormulaClicked() {
  ui_->textEdit_frml->clear();
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::OnPushButtonClearResClicked() {
  ui_->lineEdit_res->clear();
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::OnPushButtonClearXClicked() {
  ui_->lineEdit_x->clear();
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::OnPushButtonPiClicked() {
  if (ui_->lineEdit_x->hasFocus()) {
    ui_->lineEdit_x->setText("3.14159265358979323846");
  } else {
    ui_->textEdit_frml->insertPlainText("3.14159265358979323846");
    ui_->textEdit_frml->setFocus();
  }
}

void S21Viewer::OnPushButtonEClicked() {
  if (ui_->lineEdit_x->hasFocus()) {
    ui_->lineEdit_x->setText("2.71828182845904523536");
  } else {
    ui_->textEdit_frml->insertPlainText("E");
    ui_->textEdit_frml->setFocus();
  }
}

void S21Viewer::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    OnPushButtonResClicked();
  }
}

bool S21Viewer::eventFilter(QObject *watched, QEvent *event) {
  QTextEdit *textedit = qobject_cast<QTextEdit *>(watched);
  if (textedit && event->type() == QKeyEvent::KeyPress) {
    QKeyEvent *keyEvent = (QKeyEvent *)event;
    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
      OnPushButtonResClicked();
      return true;
    } else {
      return QObject::eventFilter(watched, event);
    }
  }
  return QObject::eventFilter(watched, event);
}

void S21Viewer::OnPushButtonToFormulaClicked() {
  QString string = ui_->lineEdit_res->text();
  bool ok;
  string.toDouble(&ok);
  if (ok) {
    ui_->textEdit_frml->setText(string);
  }
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::OnPushButtonResClicked() {
  std::string input_string = ui_->textEdit_frml->toPlainText().toStdString();
  std::string x_value = ui_->lineEdit_x->text().toStdString();
  std::string result = controller_->GetResult(input_string, x_value);
  ui_->lineEdit_res->setText(QString::fromStdString(result));
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::OnPushButtonGraphClicked() {
  std::string input_string = ui_->textEdit_frml->toPlainText().toStdString();
  std::string result = controller_->CheckFormula(input_string);
  if (!result.empty()) {
    DrawGraph(result);
  } else {
    ui_->lineEdit_res->setText("No graph, error in function!");
  }
  ui_->textEdit_frml->setFocus();
}

void S21Viewer::DrawGraph(std::string &out_s) {
  double xBegin, xEnd, yBegin = -1000000, yEnd = 1000000, h, Xcord,
                       Ycord = qQNaN(), Ylast, mid = 0, i = 0;
  QVector<double> x, y;
  QString string;
  ui_->lineEdit_res->clear();
  ui_->widget->clearGraphs();
  x.clear();
  y.clear();
  CheckGraphX();
  int auto_y = CheckGraphY();
  if (!auto_y) {
    string = ui_->lineEdit_yBegin->text();
    yBegin = string.toDouble();
    string = ui_->lineEdit_yEnd->text();
    yEnd = string.toDouble();
  }
  string = ui_->lineEdit_xBegin->text();
  xBegin = string.toDouble();
  string = ui_->lineEdit_xEnd->text();
  xEnd = string.toDouble();
  h = abs(xEnd - xBegin) / 20000;
  if (h < 0.00001) {
    h = 0.00001;
  }
  Xcord = xBegin;
  while (Xcord <= xEnd && h > 0) {
    Ylast = Ycord;
    if (controller_->GetValueY(out_s, Xcord, Ycord)) {
      Ycord = qQNaN();
      ui_->lineEdit_res->setText("NO graph, incorrect result!");
    }
    if (Ycord >= -1000000 && Ycord <= 1000000) {
      if (auto_y) {
        if (yBegin == -1000000) {
          yBegin = Ycord - abs(Ycord / 20);
          yEnd = Ycord + abs(Ycord / 20);
        } else {
          if ((Ycord + abs(Ycord / 20)) > yEnd) {
            yEnd = Ycord + abs(Ycord / 20);
          }
          if ((Ycord - abs(Ycord / 20)) < yBegin) {
            yBegin = Ycord - abs(Ycord / 20);
          }
        }
      }
    }
    if (Ycord == Ycord && Ycord != -qInf() && Ycord != qInf() &&
        Ylast == Ylast && Ylast != -qInf() && Ylast != qInf()) {
      mid += abs(Ycord - Ylast);
      i++;
    }
    Xcord += h;
  }
  mid /= i;
  Ycord = qQNaN();
  Xcord = xBegin;
  while (Xcord <= xEnd && h > 0) {
    Ylast = Ycord;
    if (controller_->GetValueY(out_s, Xcord, Ycord)) {
      ui_->lineEdit_res->setText("NO graph, incorrect result!");
    }
    if (abs(Ycord - Ylast) > mid * 10) {
      x.push_front(Xcord - h / 2);
      y.push_front(qQNaN());
    }
    if (Ycord >= yBegin && Ycord <= yEnd) {
      x.push_front(Xcord);
      y.push_front(Ycord);
    } else if (Ycord != Ycord && Ylast == Ylast) {
      x.push_front(Xcord);
      y.push_front(qQNaN());
    } else if ((Ycord < yBegin || Ycord == -qInf()) && Ylast != (yBegin - 1)) {
      Ycord = yBegin - 1;
      x.push_front(Xcord);
      y.push_front(Ycord);
    } else if ((Ycord > yEnd || Ycord == qInf()) && Ylast != (yEnd + 1)) {
      Ycord = yEnd + 1;
      x.push_front(Xcord);
      y.push_front(Ycord);
    }
    Xcord += h;
  }
  ui_->widget->xAxis->setRange(xBegin, xEnd);
  ui_->widget->yAxis->setRange(yBegin, yEnd);
  ui_->widget->addGraph();
  ui_->widget->setNotAntialiasedElements(QCP::aeAll);
  ui_->widget->graph(0)->setAdaptiveSampling(false);
  ui_->widget->graph(0)->setData(x, y);
  ui_->widget->replot();
}

void S21Viewer::CheckGraphX() {
  QString string = ui_->lineEdit_xBegin->text();
  double xBegin = -10, xEnd = 10;
  bool ok;
  string.toDouble(&ok);
  if (ok && string.toDouble() >= -1000000 && string.toDouble() <= 1000000) {
    xBegin = string.toDouble();
  } else {
    ui_->lineEdit_res->setText("x Min error!");
  }
  ui_->lineEdit_xBegin->setText(QString::number(xBegin));

  string = ui_->lineEdit_xEnd->text();
  string.toDouble(&ok);
  if (ok && string.toDouble() >= -1000000 && string.toDouble() <= 1000000) {
    xEnd = string.toDouble();
  } else {
    ui_->lineEdit_res->setText("x Max error!");
  }
  ui_->lineEdit_xEnd->setText(QString::number(xEnd));

  if (xBegin >= xEnd) {
    ui_->lineEdit_res->setText("x Max <= x Min!");
    if (xBegin <= 999999) {
      xEnd = xBegin + 1;
      ui_->lineEdit_xEnd->setText(QString::number(xEnd));
    } else {
      xBegin = xEnd - 1;
      ui_->lineEdit_xBegin->setText(QString::number(xBegin));
    }
  }
}

int S21Viewer::CheckGraphY() {
  QString string = ui_->lineEdit_yBegin->text();
  int err = 0;
  double yBegin = -10, yEnd = 10;
  bool ok;
  string.toDouble(&ok);
  if (ok && string.toDouble() >= -1000000 && string.toDouble() <= 1000000) {
    yBegin = string.toDouble();
  } else {
    ui_->lineEdit_res->setText("y Min error, auto value area is active!");
    err++;
  }
  string = ui_->lineEdit_yEnd->text();
  string.toDouble(&ok);
  if (ok && string.toDouble() >= -1000000 && string.toDouble() <= 1000000) {
    yEnd = string.toDouble();
  } else {
    ui_->lineEdit_res->setText("y Max error, auto value area is active!");
    err++;
  }
  if (yBegin >= yEnd) {
    ui_->lineEdit_res->setText("y Max <= y Min, auto value area is active!");
    err++;
  }
  return err;
}

void S21Viewer::OnPushButtonCreditClicked() { credit_.exec(); }

void S21Viewer::OnPushButtonDepositClicked() { deposit_.exec(); }

}  // namespace s21

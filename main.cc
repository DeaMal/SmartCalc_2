#include <QApplication>

#include "s21_calc_viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::S21Model model;
  s21::S21Controller controller(&model);
  s21::S21Viewer viewer(&controller);
  viewer.show();
  return a.exec();
}

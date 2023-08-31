#ifndef CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CONTROLLER_H_
#define CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CONTROLLER_H_

#include "s21_calc_model.h"

namespace s21 {

class S21Controller {
 public:
  S21Controller(S21Model *model) : model_(model) {}
  ~S21Controller() {}
  std::string GetResult(std::string &input_string, std::string &x);
  std::string CheckFormula(std::string &input_string);
  int GetValueY(std::string out_s, double val_x, double &result);
  int GetCreditResult(bool dif, int index, double amount, double term,
                      double rate, std::string &pay, std::string &over,
                      std::string &total);
  int GetDepositResult(double amount, double period, double rate, double tax,
                       int freq_index, int rowCountRepl, int rowCountWith,
                       double arr_repl[][2], double arr_with[][2],
                       std::string &charge, std::string &tax_amount,
                       std::string &total);

 private:
  S21Model *model_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_CONTROLLER_H_

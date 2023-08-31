#include "s21_calc_controller.h"

namespace s21 {

std::string S21Controller::GetResult(std::string &input_string,
                                     std::string &x) {
  return model_->GetCalculationResult(input_string, x);
}

std::string S21Controller::CheckFormula(std::string &input_string) {
  return model_->CheckGraphFormula(input_string);
}

int S21Controller::GetValueY(std::string out_s, double val_x, double &result) {
  return model_->Calculation(out_s, val_x, result);
}

int S21Controller::GetCreditResult(bool dif, int index, double amount,
                                   double term, double rate, std::string &pay,
                                   std::string &over, std::string &total) {
  return model_->CreditCalculation(dif, index, amount, term, rate, pay, over,
                                   total);
}

int S21Controller::GetDepositResult(double amount, double period, double rate,
                                    double tax, int freq_index,
                                    int rowCountRepl, int rowCountWith,
                                    double arr_repl[][2], double arr_with[][2],
                                    std::string &charge,
                                    std::string &tax_amount,
                                    std::string &total) {
  return model_->DepositCalculation(amount, period, rate, tax, freq_index,
                                    rowCountRepl, rowCountWith, arr_repl,
                                    arr_with, charge, tax_amount, total);
}

}  // namespace s21

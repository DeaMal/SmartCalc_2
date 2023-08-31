#ifndef CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_MODEL_H_
#define CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_MODEL_H_

#include <stack>
#include <string>

namespace s21 {

class S21Model {
 public:
  std::string GetCalculationResult(std::string &input_string, std::string &x);
  std::string CheckGraphFormula(std::string &input_string);
  int Calculation(std::string out_s, double value_x, double &result);
  int CreditCalculation(bool dif, int index, double amount, double term,
                        double rate, std::string &pay_str,
                        std::string &over_str, std::string &total_str);
  int DepositCalculation(double amount, double period, double rate, double tax,
                         int freq_index, int rowCountRepl, int rowCountWith,
                         double arr_repl[][2], double arr_with[][2],
                         std::string &charge_str, std::string &tax_amount_str,
                         std::string &total_str);

 private:
  struct Notation {
    char ch_;
    double value_;
    Notation(const char c, double v) : ch_(c), value_(v) {}
  };

  int CheckInputString(std::string &input_string);
  int PostfixNotation(std::string &input_string, std::string &out_string);
  int CloseBracket(std::stack<Notation> &elem, std::string &out_str);
  int Prioritet(char ch);
  char CheckFunc(std::string str);
  int BinaryFunc(std::stack<Notation> &elem, char ch);
  int UnaryFunc(std::stack<Notation> &elem, char ch);
  int CheckValueX(std::string val_x, double &result);
  std::string DoubleToStdString(double number, int precision, bool fixed);
};

}  // namespace s21

#endif  // CPP3_SMART_CALC_v_2_0_SRC_S21_CALC_MODEL_H_

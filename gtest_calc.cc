#include <gtest/gtest.h>

#include "s21_calc_model.h"

using namespace s21;

TEST(NOTATION, test_001) {
  S21Model m;
  std::string input_str = "35+489,99*23,7/86,00-5,34";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_input_str = "35+489.99*23.7/86.00-5.34";
  std::string check_result_str = "164.6921279069767";
  std::string check_notation_str = "35 489.99 23.7 * 86.00 / + 5.34 - ";
  std::string notation_str = "";
  double result = 0;
  double check_result = 164.6921279069767442;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_002) {
  S21Model m;
  std::string input_str = "7+8*(36+4)/5-7*99.7*(5+8*(7-2))^2";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_input_str = "7+8*(36+4)/5-7*99.7*(5+8*(7-2))^2";
  std::string check_result_str = "-1413176.5";
  std::string check_notation_str =
      "7 8 36 4 + * 5 / + 7 99.7 * 5 8 7 2 - * + 2 ^ * - ";
  std::string notation_str = "";
  double result = 0;
  double check_result = -1413176.5;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_003) {
  S21Model m;
  std::string input_str = "+,6Sin4x+5";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_input_str = "+.6sin4x+5";
  std::string check_result_str = "Incorrect input - X value is empty!";
  std::string check_notation_str = ".6 | 4 x @ s * 5 + ";
  std::string notation_str = "";
  double result = 0;
  double check_result = 5;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_004) {
  S21Model m;
  std::string input_str = "6cos-4e-2+5mod3";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_input_str = "6cos-4e-2+5mod3";
  std::string check_result_str = "7.995200639965867";
  std::string check_notation_str = "6 4e-2 ~ c * 5 3 % + ";
  std::string notation_str = "";
  double result = 0;
  double check_result = 7.9952006399658674;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_005) {
  S21Model m;
  std::string input_str = "6(tan(4)x+log5^2%2)";
  std::string check_input_str = "6(tan(4)x+log5^2%2)";
  std::string check_notation_str = "6 4 x @ t 5 2 ^ 2 % L + * ";
  std::string value_x_str = "-.0043278e+3";
  double value_x = -.0043278e+3;
  std::string check_result_str = "184.8896474989967";
  double check_result = 184.8896474989967;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_006) {
  S21Model m;
  std::string input_str = "tgsqrt24(3+2.05)45x(2^7-1)asinx";
  std::string check_input_str = "tgsqrt24(3+2.05)45x(2^7-1)asinx";
  std::string check_notation_str =
      "24 q k 3 2.05 + 45 @ x @ * 2 7 ^ 1 - * x S * ";
  std::string value_x_str = "-1";
  double value_x = -1;
  std::string check_result_str = "-240135.5535671169";
  double check_result = -240135.5535671169345733;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_007) {
  S21Model m;
  std::string input_str = "acos-4x4actg(5-2^(3+3))";
  std::string check_input_str = "acos-4x4actg(5-2^(3+3))";
  std::string check_notation_str = "4 ~ x @ 4 @ C 5 2 3 3 + ^ - G * ";
  std::string value_x_str = "0.01";
  double value_x = 0.01;
  std::string check_result_str = "5.410282348160287";
  double check_result = 5.4102823481602877;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_008) {
  S21Model m;
  std::string input_str = "2^+4xatan-4x^(4+ -2x + 2)";
  std::string check_input_str = "2^+4xatan-4x^(4+ -2x + 2)";
  std::string check_notation_str = "2 4 | x @ ^ 4 ~ x @ 4 ^ 2 ~ x @ + 2 + T * ";
  std::string value_x_str = "-0,013";
  double value_x = -0.013;
  std::string check_result_str = "1.072919263073536";
  double check_result = 1.0729192630735358;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_009) {
  S21Model m;
  std::string input_str = "((-ctg4--2ln10)";
  std::string check_input_str = "((-ctg4--2ln10)";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - \"(\" is extra!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_010) {
  S21Model m;
  std::string input_str = "(1 2-+-3w))";
  std::string check_input_str = "(1 2-+-3w))";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Symbol error!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_011) {
  S21Model m;
  std::string input_str = "sinsin5)";
  std::string check_input_str = "sinsin5)";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - \"(\" is absent!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_012) {
  S21Model m;
  std::string input_str = "+";
  std::string check_input_str = "+";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - value is absent!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_013) {
  S21Model m;
  std::string input_str = "sIcx";
  std::string check_input_str = "sicx";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - error symbol!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_014) {
  S21Model m;
  std::string input_str = "--x";
  std::string check_input_str = "--x";
  std::string check_notation_str = "";
  std::string value_x_str = "";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - two unary!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_015) {
  S21Model m;
  std::string input_str = "x+x+-x*(-x+xx-sin+x)--x";
  std::string check_input_str = "x+x+-x*(-x+xx-sin+x)--x";
  std::string check_notation_str = "x x + x ~ x ~ x x @ + x | s - * + x ~ - ";
  std::string value_x_str = "0013";
  double value_x = 13;
  std::string check_result_str = "-1983.537828521253";
  double check_result = -1983.5378285212534593;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_016) {
  S21Model m;
  std::string input_str = "ln4x";
  std::string check_input_str = "ln4x";
  std::string check_notation_str = "4 x @ l ";
  std::string value_x_str = "00t13";
  double value_x = 13;
  std::string check_result_str = "Incorrect input - X value is not correct!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  notation_str = "4 l * ";
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 1);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_017) {
  S21Model m;
  std::string input_str = "";
  std::string check_input_str = "";
  std::string check_notation_str = "";
  std::string value_x_str = "0";
  double value_x = 0;
  std::string check_result_str = "Incorrect input - formula is empty!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  notation_str = "4 g w ";
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 2);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_018) {
  S21Model m;
  std::string input_str = "-22 30e9x";
  std::string check_input_str = "-22 30e9x";
  std::string check_notation_str = "";
  std::string value_x_str = "-22E36";
  double value_x = -22E36;
  std::string check_result_str = "Incorrect input - two numbers!";
  double check_result = 0;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 3);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(NOTATION, test_019) {
  S21Model m;
  std::string input_str = "sincostanx";
  std::string check_input_str = "sincostanx";
  std::string check_notation_str = "x t c s ";
  std::string value_x_str = "2.71";
  double value_x = 2.71;
  std::string check_result_str = "0.780714343675264";
  double check_result = 0.780714343675264;
  std::string notation_str = "";
  double result = 0;

  EXPECT_EQ(m.GetCalculationResult(input_str, value_x_str), check_result_str);
  EXPECT_EQ(input_str, check_input_str);
  notation_str = m.CheckGraphFormula(input_str);
  EXPECT_EQ(notation_str, check_notation_str);
  EXPECT_EQ(m.Calculation(notation_str, value_x, result), 0);
  EXPECT_DOUBLE_EQ(result, check_result);
}

TEST(CREDIT, test_001) {
  S21Model m;
  bool dif = true;
  int index = 0;
  double amount = 100000.0;
  double term = 12.0;
  double rate = 20.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "9263.45";
  std::string check_over_str = "11161.41";
  std::string check_total_str = "111161.41";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            0);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(CREDIT, test_002) {
  S21Model m;
  bool dif = false;
  int index = 0;
  double amount = 100000.0;
  double term = 12.0;
  double rate = 20.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "10000.00~8472.22";
  std::string check_over_str = "10833.33";
  std::string check_total_str = "110833.33";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            0);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(CREDIT, test_003) {
  S21Model m;
  bool dif = false;
  int index = 1;
  double amount = 100000.0;
  double term = 1000.0;
  double rate = 20.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "Payment is too low";
  std::string check_over_str = "0.00";
  std::string check_total_str = "0.00";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            0);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(CREDIT, test_004) {
  S21Model m;
  bool dif = false;
  int index = 1;
  double amount = 464646.0;
  double term = 45649.0;
  double rate = 35.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "13.00";
  std::string check_over_str = "94748.38";
  std::string check_total_str = "559394.38";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            0);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(CREDIT, test_005) {
  S21Model m;
  bool dif = false;
  int index = 2;
  double amount = 50500.0;
  double term = 123.0;
  double rate = 24.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "2303975.58";
  std::string check_over_str = "3907524.42";
  std::string check_total_str = "6211500.00";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            0);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(CREDIT, test_006) {
  S21Model m;
  bool dif = false;
  int index = 2;
  double amount = 0.0;
  double term = 123.0;
  double rate = 24.0 / 100.0;
  std::string pay_str = "";
  std::string over_str = "";
  std::string total_str = "";
  std::string check_pay_str = "";
  std::string check_over_str = "";
  std::string check_total_str = "";
  EXPECT_EQ(m.CreditCalculation(dif, index, amount, term, rate, pay_str,
                                over_str, total_str),
            1);
  EXPECT_EQ(pay_str, check_pay_str);
  EXPECT_EQ(over_str, check_over_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(DEPOSIT, test_001) {
  S21Model m;
  double amount = 10000.0;
  double period = 50.0;
  double rate = 6.0;
  double tax = 13.0;
  int freq_index = 0;
  int rowCountRepl = 1;
  int rowCountWith = 1;
  double arr_repl[][2] = {0, 1000};
  double arr_with[][2] = {2, 1000};
  std::string charge_str = "";
  std::string tax_amount_str = "";
  std::string total_str = "";
  std::string check_charge_str = "7464.74";
  std::string check_tax_amount_str = "970.42";
  std::string check_total_str = "50494.33";
  EXPECT_EQ(m.DepositCalculation(amount, period, rate, tax, freq_index,
                                 rowCountRepl, rowCountWith, arr_repl, arr_with,
                                 charge_str, tax_amount_str, total_str),
            0);
  EXPECT_EQ(charge_str, check_charge_str);
  EXPECT_EQ(tax_amount_str, tax_amount_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(DEPOSIT, test_002) {
  S21Model m;
  double amount = 10000.0;
  double period = 50.0;
  double rate = 6.0;
  double tax = 13.0;
  int freq_index = 1;
  int rowCountRepl = 2;
  int rowCountWith = 2;
  double arr_repl[][2] = {{0, 1000}, {6, 500}};
  double arr_with[][2] = {{2, 1000}, {14, 3000}};
  std::string charge_str = "";
  std::string tax_amount_str = "";
  std::string total_str = "";
  std::string check_charge_str = "6929.94";
  std::string check_tax_amount_str = "900.89";
  std::string check_total_str = "47529.05";
  EXPECT_EQ(m.DepositCalculation(amount, period, rate, tax, freq_index,
                                 rowCountRepl, rowCountWith, arr_repl, arr_with,
                                 charge_str, tax_amount_str, total_str),
            0);
  EXPECT_EQ(charge_str, check_charge_str);
  EXPECT_EQ(tax_amount_str, tax_amount_str);
  EXPECT_EQ(total_str, check_total_str);
}

TEST(DEPOSIT, test_003) {
  S21Model m;
  double amount = 456487.0;
  double period = 34.0;
  double rate = 3.78;
  double tax = 0.50;
  int freq_index = 2;
  int rowCountRepl = 3;
  int rowCountWith = 3;
  double arr_repl[][2] = {{0, 1000.0}, {6, 500.0}, {3, 5555.0}};
  double arr_with[][2] = {{2, 1000.0}, {14, 3000.0}, {3, 555.0}};
  std::string charge_str = "";
  std::string tax_amount_str = "";
  std::string total_str = "";
  std::string check_charge_str = "53890.77";
  std::string check_tax_amount_str = "269.45";
  std::string check_total_str = "555608.32";
  EXPECT_EQ(m.DepositCalculation(amount, period, rate, tax, freq_index,
                                 rowCountRepl, rowCountWith, arr_repl, arr_with,
                                 charge_str, tax_amount_str, total_str),
            0);
  EXPECT_EQ(charge_str, check_charge_str);
  EXPECT_EQ(tax_amount_str, tax_amount_str);
  EXPECT_EQ(total_str, check_total_str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

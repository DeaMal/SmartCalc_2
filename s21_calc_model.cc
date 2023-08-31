#include "s21_calc_model.h"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <stack>

namespace s21 {

std::string S21Model::CheckGraphFormula(std::string &input_string) {
  std::string result = "";
  if (!input_string.empty() && !CheckInputString(input_string)) {
    if (PostfixNotation(input_string, result)) {
      result = "";
    }
  }
  return result;
}

std::string S21Model::GetCalculationResult(std::string &input_string,
                                           std::string &x) {
  int err = 0;
  std::string result = "";
  if (input_string.empty()) {
    result = "Incorrect input - formula is empty!";
  } else if (CheckInputString(input_string) == 0) {
    double x_value = 0;
    std::string out_string = "";
    err = PostfixNotation(input_string, out_string);
    if (!err) {
      if (input_string.find("x") == std::string::npos ||
          !CheckValueX(x, x_value)) {
        double result_d = 0;
        if (Calculation(out_string, x_value, result_d)) {
          result = "Error in notation!";
        } else {
          result = DoubleToStdString(result_d, 16, 0);
        }
      } else if (x.empty()) {
        result = "Incorrect input - X value is empty!";
      } else {
        result = "Incorrect input - X value is not correct!";
      }
    } else {
      switch (err) {
        case 1:
          result = "Incorrect input - \"(\" is absent!";
          break;
        case 2:
          result = "Incorrect input - two numbers!";
          break;
        case 3:
          result = "Incorrect input - two unary!";
          break;
        case 4:
          result = "Incorrect input - error symbol!";
          break;
        case 5:
          result = "Incorrect input - value is absent!";
          break;
        case 6:
          result = "Incorrect input - \"(\" is extra!";
          break;
        case 7:
          result = "Incorrect input - value out of range!";
          break;
        default:
          result = "Notation error!";
          break;
      }
    }
  } else {
    result = "Symbol error!";
  }
  return result;
}

int S21Model::CheckInputString(std::string &input_string) {
  int err = 0;
  std::string pattern = "0123456789+-/*%.,()^xmodcsintaqrlgeXMODCSINTAQRLGE ";
  for (size_t i = 0; i < input_string.size() && !err; i++) {
    if (pattern.find(input_string[i]) == std::string::npos) {
      err++;
    } else {
      if (input_string[i] > 64 && input_string[i] < 91) {
        input_string[i] += 32;
      }
      if (input_string[i] == ',') {
        input_string[i] = '.';
      }
    }
  }
  return err;
}

int S21Model::PostfixNotation(std::string &input_string,
                              std::string &out_string) {
  int err = 0, bkt = 0, prev = 0;
  char check_ch = '\0';
  std::stack<Notation> n_stack;
  n_stack.emplace('\0', 0);
  std::string out_str = "";
  for (size_t j = 0; j < input_string.size() && !err; ++j) {
    if (input_string[j] == ')' && prev > 1) {
      bkt++;
      while (bkt > 0) {
        err = CloseBracket(n_stack, out_str);
        bkt--;
      }
      prev = 2;

    } else if (input_string[j] == '(') {
      while (prev > 2 && bkt > 0) {
        err = CloseBracket(n_stack, out_str);
        bkt--;
      }
      if (prev > 1) {
        while (n_stack.top().ch_ != '\0' &&
               Prioritet(n_stack.top().ch_) >= Prioritet('*')) {
          out_str += n_stack.top().ch_;
          out_str += " ";
          n_stack.pop();
        }
        n_stack.emplace('*', 0);
      }
      n_stack.emplace('(', 0);
      prev = 0;
    } else if (input_string[j] == 'x' || input_string[j] == 'X') {
      if (prev > 1) {
        while (n_stack.top().ch_ != '\0' &&
               Prioritet(n_stack.top().ch_) >= Prioritet('@')) {
          out_str += n_stack.top().ch_;
          out_str += " ";
          n_stack.pop();
        }
        n_stack.emplace('@', 0);
      }
      if (prev == 1) {
        n_stack.emplace('(', 0);
        bkt++;
      }
      out_str += "x ";
      prev = 4;
    } else if ((input_string[j] >= '0' && input_string[j] <= '9') ||
               (input_string[j] == '.' && input_string[j + 1] >= '0' &&
                input_string[j + 1] <= '9')) {
      if (prev > 1) {
        while (n_stack.top().ch_ != '\0' &&
               Prioritet(n_stack.top().ch_) >= Prioritet('@')) {
          out_str += n_stack.top().ch_;
          out_str += " ";
          n_stack.pop();
        }
        n_stack.emplace('@', 0);
      }
      if (prev == 1) {
        n_stack.emplace('(', 0);
        bkt++;
      }
      if (prev != 3) {
        size_t shift;
        try {
          std::stod(input_string.substr(j), &shift);
        } catch (const std::out_of_range &oor) {
          err = 7;
        }
        out_str += input_string.substr(j, shift);
        out_str += " ";
        j += static_cast<int>(shift) - 1;
        prev = 3;
      } else {
        err = 2;
      }
    } else if ((check_ch = CheckFunc(input_string.substr(j))) != '\0') {
      while (prev > 2 && bkt > 0) {
        err = CloseBracket(n_stack, out_str);
        bkt--;
      }
      if (prev > 1) {
        while (n_stack.top().ch_ != '\0' &&
               Prioritet(n_stack.top().ch_) >= Prioritet('*')) {
          out_str += n_stack.top().ch_;
          out_str += " ";
          n_stack.pop();
        }
        n_stack.emplace('*', 0);
      }
      if (prev == 1) {
        n_stack.emplace('(', 0);
        bkt++;
      }
      while (n_stack.top().ch_ != '\0' &&
             Prioritet(n_stack.top().ch_) == Prioritet('s')) {
        out_str += n_stack.top().ch_;
        out_str += " ";
        n_stack.pop();
      }
      n_stack.emplace(check_ch, 0);
      if (check_ch == 'S' || check_ch == 'C' || check_ch == 'T' ||
          check_ch == 'G' || check_ch == 'q') {
        j += 3;
      } else if (check_ch == 'k' || check_ch == 'l') {
        j += 1;
      } else {
        j += 2;
      }
      prev = 1;
    } else if ((input_string.substr(j).find("mod") == 0 ||
                input_string[j] == '%') &&
               prev > 1) {
      while (n_stack.top().ch_ != '\0' &&
             Prioritet(n_stack.top().ch_) >= Prioritet('%')) {
        out_str += n_stack.top().ch_;
        out_str += " ";
        n_stack.pop();
      }
      n_stack.emplace('%', 0);
      if (input_string[j] != '%') {
        j += 2;
      }
      prev = 0;
    } else if (input_string[j] == '^' && prev > 1) {
      while (n_stack.top().ch_ != '\0' &&
             Prioritet(n_stack.top().ch_) >= Prioritet('^')) {
        out_str += n_stack.top().ch_;
        out_str += " ";
        n_stack.pop();
      }
      n_stack.emplace('^', 0);
      prev = 0;
    } else if ((input_string[j] == '*' || input_string[j] == '/' ||
                input_string[j] == '+' || input_string[j] == '-') &&
               prev > 1) {
      while (prev > 2 && bkt > 0) {
        err = CloseBracket(n_stack, out_str);
        bkt--;
      }
      while (n_stack.top().ch_ != '\0' &&
             Prioritet(n_stack.top().ch_) >= Prioritet(input_string[j])) {
        out_str += n_stack.top().ch_;
        out_str += " ";
        n_stack.pop();
      }
      n_stack.emplace(input_string[j], 0);
      prev = 0;
    } else if (input_string[j] == '+' || input_string[j] == '-') {
      if (prev == 1) {
        n_stack.emplace('(', 0);
        bkt++;
      }
      if (Prioritet(n_stack.top().ch_) != Prioritet('~')) {
        n_stack.emplace(input_string[j] + 81, 0);
        prev = 0;
      } else {
        err = 3;
      }
    } else if (input_string[j] == ' ') {
    } else {
      err = 4;
    }
  }
  if (prev > 1 && !err) {
    while (bkt > 0 && !err) {
      err = CloseBracket(n_stack, out_str);
      bkt--;
    }
  } else if (!err) {
    err = 5;
  }
  while (n_stack.top().ch_ != '\0' && !err) {
    if (n_stack.top().ch_ != '(') {
      out_str += n_stack.top().ch_;
      out_str += " ";
      n_stack.pop();
    } else {
      err = 6;
    }
  }
  if (!err && !out_str.empty()) {
    out_string = out_str;
  } else {
    out_str.clear();
  }
  return err;
}

int S21Model::CloseBracket(std::stack<Notation> &elem, std::string &out_str) {
  int err = 0;
  while (elem.top().ch_ != '(' && elem.top().ch_ != '\0') {
    out_str += elem.top().ch_;
    out_str += " ";
    elem.pop();
  }
  if (elem.top().ch_ == '(') {
    elem.pop();
  } else {
    err++;
  }
  return err;
}

int S21Model::Prioritet(char ch) {
  int res = 0;
  if (ch == '(' || ch == ')') {
    res = 1;
  } else if (ch == '+' || ch == '-') {
    res = 2;
  } else if (ch == '*' || ch == '/') {
    res = 3;
  } else if (ch == '%') {
    res = 4;
  } else if (ch == '^') {
    res = 5;
  } else if (ch == 's' || ch == 'c' || ch == 't' || ch == 'k' || ch == 'C' ||
             ch == 'S' || ch == 'T' || ch == 'l' || ch == 'L' || ch == 'g' ||
             ch == 'G' || ch == 'q') {
    res = 6;
  } else if (ch == '@') {
    res = 7;
  } else if (ch == '~' || ch == '|') {
    res = 8;
  }
  return res;
}

char S21Model::CheckFunc(std::string str) {
  char res = '\0';
  if (str.find("asin") == 0) {
    res = 'S';
  } else if (str.find("sin") == 0) {
    res = 's';
  } else if (str.find("acos") == 0) {
    res = 'C';
  } else if (str.find("cos") == 0) {
    res = 'c';
  } else if (str.find("atan") == 0) {
    res = 'T';
  } else if (str.find("tan") == 0) {
    res = 't';
  } else if (str.find("actg") == 0) {
    res = 'G';
  } else if (str.find("ctg") == 0) {
    res = 'g';
  } else if (str.find("tg") == 0) {
    res = 'k';
  } else if (str.find("ln") == 0) {
    res = 'l';
  } else if (str.find("log") == 0) {
    res = 'L';
  } else if (str.find("sqrt") == 0) {
    res = 'q';
  }
  return res;
}

int S21Model::Calculation(std::string out_s, double value_x, double &result) {
  int err = 0;
  double val1 = 0;
  std::string pattern = "-+/*@%^";
  std::string pattern2 = "sctkCSTlLgGq~";
  std::stack<Notation> c_stack;
  size_t s_pos = 0, n_pos = 0;
  n_pos = out_s.find(" ", s_pos);
  while (n_pos != std::string::npos && !err) {
    std::string tmp_s = out_s.substr(s_pos, n_pos - s_pos);
    if (tmp_s[0] == 'x') {
      c_stack.emplace('x', value_x);
    } else if ((tmp_s[0] >= '0' && tmp_s[0] <= '9') ||
               (tmp_s[0] == '.' && tmp_s[1] >= '0' && tmp_s[1] <= '9')) {
      try {
        c_stack.emplace('x', std::stod(tmp_s));
      } catch (const std::out_of_range &oor) {
        err = 7;
      }
    } else if (pattern.find(tmp_s[0]) != std::string::npos) {
      err = BinaryFunc(c_stack, tmp_s[0]);
    } else if (pattern2.find(tmp_s[0]) != std::string::npos) {
      err = UnaryFunc(c_stack, tmp_s[0]);
    } else if (tmp_s[0] == ' ' || tmp_s[0] == '|') {
    } else {
      err = 2;
    }
    s_pos = n_pos + 1;
    n_pos = out_s.find(" ", s_pos);
  }
  if (!err) {
    if (c_stack.empty()) {
      err = 3;
    } else {
      val1 = c_stack.top().value_;
      c_stack.pop();
    }
    if (c_stack.empty()) {
      result = val1;
    } else {
      err = 4;
    }
  }
  return err;
}

int S21Model::BinaryFunc(std::stack<Notation> &elem, char ch) {
  int err = 0;
  double val1 = 0, val2 = 0;
  //    char temp_ch = '\0';
  if (!elem.empty()) {
    val1 = elem.top().value_;
    elem.pop();
    if (!elem.empty()) {
      val2 = elem.top().value_;
      elem.pop();
      if (ch == '-') {
        elem.emplace('x', val2 - val1);
      } else if (ch == '+') {
        elem.emplace('x', val2 + val1);
      } else if (ch == '*' || ch == '@') {
        elem.emplace('x', val2 * val1);
      } else if (ch == '/') {
        elem.emplace('x', val2 / val1);
      } else if (ch == '%') {
        elem.emplace('x', fmod(val2, val1));
      } else if (ch == '^') {
        elem.emplace('x', pow(val2, val1));
      } else {
        err++;
      }
    } else {
      err++;
    }
  } else {
    err++;
  }
  return err;
}

int S21Model::UnaryFunc(std::stack<Notation> &elem, char ch) {
  const double pi = 3.14159265358979323846;
  int err = 0;
  double val = 0;
  if (!elem.empty()) {
    val = elem.top().value_;
    elem.pop();
    if (ch == '~') {
      elem.emplace('x', -1 * val);
    } else if (ch == 's') {
      elem.emplace('x', sin(val));
    } else if (ch == 'S') {
      elem.emplace('x', asin(val));
    } else if (ch == 'c') {
      elem.emplace('x', cos(val));
    } else if (ch == 'C') {
      elem.emplace('x', acos(val));
    } else if (ch == 't' || ch == 'k') {
      elem.emplace('x', tan(val));
    } else if (ch == 'T') {
      elem.emplace('x', atan(val));
    } else if (ch == 'l') {
      elem.emplace('x', log10(val));
    } else if (ch == 'L') {
      elem.emplace('x', log(val));
    } else if (ch == 'q') {
      elem.emplace('x', sqrt(val));
    } else if (ch == 'g') {
      elem.emplace('x', 1 / tan(val));
    } else if (ch == 'G') {
      elem.emplace('x', pi / 2 - atan(val));
    } else {
      err++;
    }
  } else {
    err++;
  }
  return err;
}

int S21Model::CheckValueX(std::string val_x, double &result) {
  int err = 0, k = 0;
  for (size_t i = 0; i < val_x.size(); ++i) {
    if (val_x[i] == ',') {
      val_x[i] = '.';
    }
  }
  if (val_x[k] == '-' || val_x[k] == '+') {
    k++;
  }
  if ((val_x[k] >= '0' && val_x[k] <= '9') ||
      (val_x[k] == '.' && val_x[k + 1] >= '0' && val_x[k + 1] <= '9')) {
    size_t shift;
    double digit = 0;
    try {
      digit = std::stod(val_x, &shift);
    } catch (const std::out_of_range &oor) {
      err = 7;
    }
    if (shift < val_x.size()) {
      err++;
    } else {
      result = digit;
    }
  } else {
    err++;
  }
  return err;
}

std::string S21Model::DoubleToStdString(double number, int precision,
                                        bool fixed) {
  std::ostringstream stream_result;
  stream_result.precision(precision);
  if (fixed) {
    stream_result << std::fixed;
  }
  //  stream_result << std::setprecision(precision);
  stream_result << number;
  return stream_result.str();
}

int S21Model::CreditCalculation(bool dif, int index, double amount, double term,
                                double rate, std::string &pay_str,
                                std::string &over_str, std::string &total_str) {
  int err = 0;
  if (amount > 0 && term > 0 && rate > 0) {
    double pay = 0, over = 0, total = 0, last = 0;
    if (index == 0) {
      if (dif) {
        pay = amount * rate * pow(1 + rate / 12, term) /
              (12 * (pow(1 + rate / 12, term) - 1));
        pay_str = DoubleToStdString(pay, 2, 1);
        over = pay * term - amount;
      } else {
        double fstpay = 0, lstpay = 0;
        int i = term;
        last = amount;
        while (i) {
          pay = amount / term + last * rate / 12;
          if (pay > fstpay) {
            fstpay = pay;
          } else {
            lstpay = pay;
          }
          total += pay;
          last -= amount / term;
          i--;
        }
        pay_str = DoubleToStdString(fstpay, 2, 1);
        pay_str += '~';
        pay_str += DoubleToStdString(lstpay, 2, 1);
        over = total - amount;
      }
    } else if (index == 1) {
      if (amount * rate / 12 >= term) {
        pay_str = "Payment is too low";
        over = 0;
        amount = 0;
      } else {
        last = amount;
        while (last > 0) {
          pay++;
          over += last * rate / 12;
          last += (last * rate / 12) - term;
        }
        pay_str = DoubleToStdString(pay, 2, 1);
      }
    } else {
      total = amount * term;
      pay = amount * (12 * (pow(1 + rate / 12, term) - 1)) /
            (rate * pow(1 + rate / 12, term));
      pay_str = DoubleToStdString(pay, 2, 1);
      over = total - pay;
    }
    over_str = DoubleToStdString(over, 2, 1);
    if (index != 2) {
      total = over + amount;
    }
    total_str = DoubleToStdString(total, 2, 1);
  } else {
    err++;
  }
  return err;
}

int S21Model::DepositCalculation(double amount, double period, double rate,
                                 double tax, int freq_index, int rowCountRepl,
                                 int rowCountWith, double arr_repl[][2],
                                 double arr_with[][2], std::string &charge_str,
                                 std::string &tax_amount_str,
                                 std::string &total_str) {
  int err = 0;
  double charge = 0, tax_amount = 0, total = 0;
  if (amount != 0 && period != 0 && rate != 0) {
    double amount_temp = amount;
    if (freq_index < 2) {
      for (int i = 0; i < period / 12.0 * 365.0; i++) {
        charge += (amount_temp * rate / 365.0 / 100.0);
        if (freq_index == 0) {
          amount_temp += charge;
          charge = 0;
        } else if (freq_index == 1 && (((i + 1) % 7 == 0) ||
                                       ((i + 1) >= (period / 12.0 * 365.0)))) {
          amount_temp += charge;
          charge = 0;
        }
        if (rowCountRepl > 0) {
          for (int k = 0; k < rowCountRepl; k++) {
            if ((arr_repl[k][0] == 0 && ((i + 1) % 30 == 0)) ||
                (arr_repl[k][0] == 1 && ((i + 1) % 60 == 0)) ||
                (arr_repl[k][0] == 2 && ((i + 1) % 91 == 0)) ||
                (arr_repl[k][0] == 3 && ((i + 1) % 182 == 0)) ||
                (arr_repl[k][0] == 4 && ((i + 1) % 365 == 0)) ||
                (arr_repl[k][0] * 30 == (121 + i))) {
              amount_temp += arr_repl[k][1];
              amount += arr_repl[k][1];
            }
          }
        }
        if (rowCountWith > 0) {
          for (int k = 0; k < rowCountWith; k++) {
            if ((arr_with[k][0] == 0 && ((i + 1) % 30 == 0)) ||
                (arr_with[k][0] == 1 && ((i + 1) % 60 == 0)) ||
                (arr_with[k][0] == 2 && ((i + 1) % 91 == 0)) ||
                (arr_with[k][0] == 3 && ((i + 1) % 182 == 0)) ||
                (arr_with[k][0] == 4 && ((i + 1) % 365 == 0)) ||
                (arr_with[k][0] * 30 == (121 + i))) {
              if (amount_temp - arr_with[k][1] > 0) {
                amount_temp -= arr_with[k][1];
                amount -= arr_with[k][1];
              }
            }
          }
        }
      }
    } else {
      for (int i = 1; i <= period; i++) {
        charge += (amount_temp * rate / 12 / 100);
        if ((freq_index == 2) ||
            (freq_index == 3 && (i % 3 == 0 || i == period)) ||
            (freq_index == 4 && (i % 6 == 0 || i == period)) ||
            (freq_index == 5 && (i % 12 == 0 || i == period)) ||
            (freq_index == 6 && i == period)) {
          amount_temp += charge;
          charge = 0;
        }
        if (rowCountRepl > 0) {
          for (int k = 0; k < rowCountRepl; k++) {
            if ((arr_repl[k][0] == 0) ||
                (arr_repl[k][0] == 1 && (i % 2 == 0)) ||
                (arr_repl[k][0] == 2 && (i % 3 == 0)) ||
                (arr_repl[k][0] == 3 && (i % 6 == 0)) ||
                (arr_repl[k][0] == 4 && (i % 12 == 0)) ||
                (arr_repl[k][0] == (4 + i))) {
              amount_temp += arr_repl[k][1];
              amount += arr_repl[k][1];
            }
          }
        }
        if (rowCountWith > 0) {
          for (int k = 0; k < rowCountWith; k++) {
            if ((arr_with[k][0] == 0) ||
                (arr_with[k][0] == 1 && (i % 2 == 0)) ||
                (arr_with[k][0] == 2 && (i % 3 == 0)) ||
                (arr_with[k][0] == 3 && (i % 6 == 0)) ||
                (arr_with[k][0] == 4 && (i % 12 == 0)) ||
                (arr_with[k][0] == (4 + i))) {
              if (amount_temp - arr_with[k][1] > 0) {
                amount_temp -= arr_with[k][1];
                amount -= arr_with[k][1];
              }
            }
          }
        }
      }
    }
    charge = amount_temp - amount;
    tax_amount = charge * tax / 100.0;
    total = charge + amount - tax_amount;

    charge_str = DoubleToStdString(charge, 2, 1);
    tax_amount_str = DoubleToStdString(tax_amount, 2, 1);
    total_str = DoubleToStdString(total, 2, 1);
  } else {
    err++;
  }
  return err;
}

}  // namespace s21

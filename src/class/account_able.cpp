
#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <ios> // fixed

#include "account_able.hpp"

namespace Wallet
{
  void AccountAble::setRevenue(AccountAble::Number _revenue) noexcept
  {
    this->revenue = _revenue;
    this->calcBalance();
  }

  std::string AccountAble::getRevenueStr() const noexcept
  {
    std::stringstream ss;
    if (this->revenue > 0.0) {
      ss << std::fixed << std::setprecision(2) << this->revenue;
    }
    return ss.str();
  }

  void AccountAble::setExpense(AccountAble::Number _expense) noexcept
  {
    this->expense = -std::abs(_expense);
    this->calcBalance();
  }

  std::string AccountAble::getExpenseStr() const noexcept
  {
    std::stringstream ss;
    if (this->expense < 0.0) {
      ss << std::fixed << std::setprecision(2) << this->expense;
    }
    return ss.str();
  }

  std::string AccountAble::getBalanceStr() const noexcept
  {
    std::stringstream ss;
    if (this->balance != 0.0) {
      ss << std::fixed << std::setprecision(2) << this->balance;
    }
    return ss.str();
  }

  void AccountAble::calcBalance() noexcept
  {
    this->balance = this->revenue + this->expense;
  }
} // Wallet Namespace

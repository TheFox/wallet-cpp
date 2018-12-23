
#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <ios> // fixed

#include "accountable.hpp"

namespace Wallet
{
  void Accountable::setRevenue(Accountable::Number _revenue) noexcept
  {
    this->revenue = _revenue;
    this->calcBalance();
  }

  std::string Accountable::getRevenueStr() const noexcept
  {
    std::stringstream ss;
    if (this->revenue > 0.0) {
      ss << std::fixed << std::setprecision(2) << this->revenue;
    }
    return ss.str();
  }

  void Accountable::setExpense(Accountable::Number _expense) noexcept
  {
    this->expense = -std::abs(_expense);
    this->calcBalance();
  }

  std::string Accountable::getExpenseStr() const noexcept
  {
    std::stringstream ss;
    if (this->expense < 0.0) {
      ss << std::fixed << std::setprecision(2) << this->expense;
    }
    return ss.str();
  }

  std::string Accountable::getBalanceStr() const noexcept
  {
    std::stringstream ss;
    if (this->balance != 0.0) {
      ss << std::fixed << std::setprecision(2) << this->balance;
    }
    return ss.str();
  }

  void Accountable::calcBalance() noexcept
  {
    this->balance = this->revenue + this->expense;
  }
} // Wallet Namespace

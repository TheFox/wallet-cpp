
#include <sstream> // ostringstream
#include <iomanip> // setprecision
#include <ios> // fixed

#include "accountable.hpp"

namespace Wallet
{
  void Accountable::setRevenue(Accountable::Number _revenue) noexcept
  {
    this->revenueCache = false;
    this->revenue = _revenue;
    this->calcBalance();
  }

  std::string Accountable::getRevenueStr() const noexcept
  {
    if (this->revenueCache) {
      return this->revenueStr;
    }
    this->revenueCache = true;

    std::ostringstream ss{};
    if (this->revenue > 0.0) {
      ss << std::fixed << std::setprecision(2) << this->revenue;
    }

    this->revenueStr = ss.str();
    return this->revenueStr;
  }

  void Accountable::setExpense(Accountable::Number _expense) noexcept
  {
    this->expenseCache = false;
    this->expense = -std::abs(_expense);
    this->calcBalance();
  }

  std::string Accountable::getExpenseStr() const noexcept
  {
    if (this->expenseCache) {
      return this->expenseStr;
    }

    std::ostringstream ss{};
    if (this->expense < 0.0) {
      ss << std::fixed << std::setprecision(2) << this->expense;
    }
    this->expenseStr = ss.str();
    return this->expenseStr;
  }

  std::string Accountable::getBalanceStr() const noexcept
  {
    if (this->balanceCache) {
      return this->balanceStr;
    }

    std::ostringstream ss{};
    if (this->balance != 0.0) {
      ss << std::fixed << std::setprecision(2) << this->balance;
    }
    this->balanceStr = ss.str();
    return this->balanceStr;
  }

  void Accountable::calcBalance() noexcept
  {
    this->balanceCache = false;
    this->balance = this->revenue + this->expense;
  }

  /**
   * Get HTML class based on the Balance.
   */
  std::string Accountable::getBalanceHtmlClass() const noexcept
  {
    if (this->balance < 0) {
      return "red";
    }

    return "";
  }
} // Wallet Namespace

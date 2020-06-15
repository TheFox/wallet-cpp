
#include <sstream> // ostringstream
#include <iomanip> // setprecision
#include <ios> // fixed

#include "debug.hpp"
#include "accountable.hpp"

namespace Wallet::Trait
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

  std::string Accountable::getRevenuePercentStr() const noexcept
  {
    if (this->revenuePercentCache) {
      return this->revenuePercentStr;
    }
    this->revenuePercentCache = true;

    std::ostringstream ss{};
    ss << std::fixed << std::setprecision(2) << this->revenuePercent;
    this->revenuePercentStr = ss.str();
    //DLog("-> Accountable::getRevenuePercentStr() -> '%s'\n", this->revenuePercentStr.c_str());
    return this->revenuePercentStr;
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
    this->expenseCache = true;

    std::ostringstream ss{};
    if (this->expense < 0.0) {
      ss << std::fixed << std::setprecision(2) << this->expense;
    }
    this->expenseStr = ss.str();
    return this->expenseStr;
  }

  std::string Accountable::getExpensePercentStr() const noexcept
  {
    if (this->expensePercentCache) {
      return this->expensePercentStr;
    }
    this->expensePercentCache = true;

    std::ostringstream ss{};
    ss << std::fixed << std::setprecision(2) << this->expensePercent;
    this->expensePercentStr = ss.str();

    //DLog("-> Accountable::getExpensePercentStr() -> '%s'\n", this->expensePercentStr.c_str());
    return this->expensePercentStr;
  }

  std::string Accountable::getBalanceStr() const noexcept
  {
    if (this->balanceCache) {
      return this->balanceStr;
    }
    this->balanceCache = true;

    std::ostringstream ss{};
    if (this->balance != 0.0) {
      ss << std::fixed << std::setprecision(2) << this->balance;
    }
    this->balanceStr = ss.str();
    return this->balanceStr;
  }

  std::string Accountable::getBalancePercentStr() const noexcept
  {
    if (this->balancePercentCache) {
      return this->balancePercentStr;
    }
    this->balancePercentCache = true;

    std::ostringstream ss{};
    if (this->balancePercent != 0.0) {
      ss << std::fixed << std::setprecision(2) << this->balancePercent;
    }
    this->balancePercentStr = ss.str();
    return this->balancePercentStr;
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
} // Wallet::Trait Namespace

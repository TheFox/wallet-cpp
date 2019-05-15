
#ifndef WALLETCPP_TRAIT_ACCOUNTABLE_HPP_
#define WALLETCPP_TRAIT_ACCOUNTABLE_HPP_

#include <string>
#include <cmath> // float_t

namespace Wallet::Trait
{
  class Accountable
  {
  public:
    // Types
    using Number = std::float_t;

    // Parameter: Revenue
    void setRevenue(Number) noexcept;
    std::string getRevenueStr() const noexcept;

    // Parameter: Expense
    void setExpense(Number) noexcept;
    std::string getExpenseStr() const noexcept;

    // Parameter: Balance
    std::string getBalanceStr() const noexcept;
    std::string getBalancePercentStr() const noexcept;

    // Properties
    Number revenue{};
    Number expense{};
    Number balance{};
    Number balanceAbs{};
    std::float_t balancePercent{};

    // Functions
    void calcBalance() noexcept;
    std::string getBalanceHtmlClass() const noexcept;

  private:
    // Properties
    mutable bool revenueCache{};
    mutable std::string revenueStr{};

    mutable bool expenseCache{};
    mutable std::string expenseStr{};

    mutable bool balanceCache{};
    mutable std::string balanceStr{};

    mutable bool balancePercentCache{};
    mutable std::string balancePercentStr{};
  };
} // Wallet::Trait Namespace

#endif // WALLETCPP_TRAIT_ACCOUNTABLE_HPP_


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

    // Properties
    Number revenue{};
    Number expense{};
    Number balance{};

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
  };
} // Wallet::Trait Namespace

#endif // WALLETCPP_TRAIT_ACCOUNTABLE_HPP_

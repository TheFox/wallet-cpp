
#ifndef WALLETCPP_ACCOUNT_ABLE_HPP_
#define WALLETCPP_ACCOUNT_ABLE_HPP_

#include <string>
#include <cmath> // float_t

namespace Wallet
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

    // Parameter: Balance
    //std::string getBalanceSumStr() const noexcept;

    // Properties
    Number revenue{};
    Number expense{};
    Number balance{};
    //Number balanceSum{};

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
    //mutable bool balanceSumCache{};
    //mutable std::string balanceSumStr{};
  };
} // Wallet Namespace

#endif // WALLETCPP_ACCOUNT_ABLE_HPP_

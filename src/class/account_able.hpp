
#ifndef WALLETCPP_ACCOUNT_ABLE_HPP_
#define WALLETCPP_ACCOUNT_ABLE_HPP_

#include <string>
#include <cmath>

namespace Wallet
{
  struct AccountAble
  {
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

    // Variables
    Number revenue{};
    Number expense{};
    Number balance{};

    // Functions
    void calcBalance() noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_ACCOUNT_ABLE_HPP_

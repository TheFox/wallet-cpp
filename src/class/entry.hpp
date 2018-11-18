
#ifndef WALLETCPP_ENTRY_HPP_
#define WALLETCPP_ENTRY_HPP_

#include <string>
#include <cmath>

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#endif // __has_include

#include "command_options.hpp"

namespace Wallet
{
  class Entry final
  {
  public:
    // Constructor
    Entry() noexcept;

    // Copy Contructor
    Entry(const CommandOptions&) noexcept;

    // Destructor
    ~Entry() noexcept;

    // Parameter: ID
    void setId(std::string) noexcept;
    std::string getId() const noexcept;

    // Parameter: Title
    void setTitle(std::string) noexcept;
    std::string getTitle() const noexcept;

    // Parameter: Date
    void setDate(std::string);
    std::string getDateStr() const noexcept;

    // Parameter: Revenue
    void setRevenue(std::float_t) noexcept;
    std::float_t getRevenue() const noexcept;

    // Parameter: Expense
    void setExpense(std::float_t) noexcept;
    std::float_t getExpense() const noexcept;

    // Parameter: Balance
    void calcBalance() noexcept;
    std::float_t getBalance() const noexcept;

    // Parameter: Category
    void setCategory(std::string) noexcept;
    std::string getCategory() const noexcept;

    // Parameter: Comment
    void setComment(std::string) noexcept;
    std::string getComment() const noexcept;

    // Functions
    void generateRandomId() noexcept;
    std::string getFileName() const noexcept;

    // Conversion
    template<typename T>
    T as() const noexcept;

  private:
    // Variables
    std::string id{};
    std::string title{};
    gregorian::date date{};
    std::float_t revenue{};
    std::float_t expense{};
    std::float_t balance{};
    std::string category{};
    std::string comment{};
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_

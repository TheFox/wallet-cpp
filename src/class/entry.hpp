
#ifndef WALLETCPP_ENTRY_HPP_
#define WALLETCPP_ENTRY_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#endif // __has_include

namespace Wallet
{
  class Entry final
  {
  public:
    // Constructor
    Entry();

    // Destructor
    ~Entry();

    // Parameter: ID
    void setId(std::string) noexcept;
    std::string getId() const noexcept;

    // Parameter: Title
    void setTitle(std::string) noexcept;
    std::string getTitle() const noexcept;

    // Parameter: Date
    void setDate(std::string);
    std::string getDateStr() const noexcept;

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

    // Functions
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_

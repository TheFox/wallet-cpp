
#ifndef WALLETCPP_ENTRY_HPP_
#define WALLETCPP_ENTRY_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace calendar = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "epic.hpp"
#include "trait/accountable.hpp"
#include "command/command_options.hpp"
#include "trait/idable.hpp"

namespace Wallet
{
  class Entry final : public Trait::Accountable, public Trait::Idable
  {
  public:
    // Constructor
    Entry() noexcept;

    // Copy Contructor
    explicit Entry(const CommandOptions&);
    explicit Entry(const YAML::Node&) noexcept;

    // Parameter: Title
    std::string title{};

    // Parameter: Date
    void setDate(const std::string&);
    std::string getDateStr() const noexcept;

    // Parameter: Category
    std::string category{};
    std::string getCategoryHtml() const noexcept;

    // Parameter: Epic Handle
    //Epic epic{};
    std::string epicHandle{};
    std::string getEpicHandleHtml() const noexcept;
    bool hasDefaultEpic() const noexcept;

    // Parameter: Comment
    std::string comment{};

    // Functions
    std::string getFileName() const noexcept;

    // Conversion
    template<typename T>
    T as() const noexcept;

  private:
    // Variables
    calendar::date date{};
  };
} // Wallet Namespace

#endif // WALLETCPP_ENTRY_HPP_

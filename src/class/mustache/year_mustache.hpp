
#ifndef WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_

#include <string>

#include "base_mustache.hpp"
#include "class/container/entry_container.hpp"

namespace Wallet::Mustache
{
  class YearMustache final : public BaseMustache
  {
  public:
    // Constructor
    YearMustache(std::string, mstch::array, mstch::map, std::string, Container::CategoryArray);

  private:
    // Properties
    const std::string year{};
    const Container::CategoryArray categoryNames{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getCategoryCount() noexcept;
    mstch::node getCategories() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_YEAR_MUSTACHE_HPP_

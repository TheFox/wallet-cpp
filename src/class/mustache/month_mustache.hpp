
#ifndef WALLETCPP_MUSTACHE_MONTH_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_MONTH_MUSTACHE_HPP_

#include <string>

#include "base_mustache.hpp"

namespace Wallet::Mustache
{
  class MonthMustache final : public BaseMustache
  {
  public:
    // Constructor
    MonthMustache(std::string, mstch::array, mstch::map, std::string, std::string, std::string, bool);

  private:
    // Properties
    const std::string year{};
    const std::string month{};
    const std::string fileName{};
    const bool showEpics{};

    // Functions
    mstch::node getYear() noexcept;
    mstch::node getMonth() noexcept;
    mstch::node getFileName() noexcept;
    mstch::node getShowEpics() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_MONTH_MUSTACHE_HPP_

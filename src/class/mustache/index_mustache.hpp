
#ifndef WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_

#include "base_mustache.hpp"
#include "class/container/epic_container.hpp"

namespace Wallet::Mustache
{
  class IndexMustache final : public BaseMustache
  {
  public:
    // Constructor
    IndexMustache(mstch::array, mstch::map, mstch::array);

  private:
    // Properties
    const mstch::array epics{};

    // Functions
    mstch::node getEpicCount() noexcept;
    mstch::node getEpics() noexcept;
    mstch::node getHasEpics() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_

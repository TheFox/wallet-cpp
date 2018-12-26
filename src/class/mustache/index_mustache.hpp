
#ifndef WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_

#include "base_mustache.hpp"

namespace Wallet::Mustache
{
  class IndexMustache final : public BaseMustache
  {
  public:
    // Constructor
    IndexMustache(mstch::array, mstch::map);
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_INDEX_MUSTACHE_HPP_

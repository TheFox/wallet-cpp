
#include "debug.hpp"
#include "config.hpp"
#include "index_mustache.hpp"

namespace Wallet::Mustache
{
  IndexMustache::IndexMustache(mstch::array _entries, mstch::map _total) :
    BaseMustache{std::move(_entries), std::move(_total)}
  {
    //DLog(" -> IndexMustache::IndexMustache() -> %lu entries, %lu totals\n", this->entries.size(), this->total.size());
  }
} // Wallet::Mustache Namespace

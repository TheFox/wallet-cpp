
#include "debug.hpp"
#include "config.hpp"
#include "index_mustache.hpp"

namespace Wallet::Mustache
{
  IndexMustache::IndexMustache(mstch::array _entries, mstch::map _total) :
    BaseMustache{std::move(_entries), std::move(_total)}
  {
    //DLog(" -> IndexMustache::IndexMustache()\n");
  }
} // Wallet::Mustache Namespace

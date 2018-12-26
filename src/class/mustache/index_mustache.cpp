
#include "debug.hpp"
#include "index_mustache.hpp"

namespace Wallet::Mustache
{
  IndexMustache::IndexMustache(mstch::array _entries, mstch::map _total) :
    BaseMustache(std::move(_entries), std::move(_total))
  {
    //DLog(" -> IndexMustache::IndexMustache()\n");

    this->register_methods(this, {
      {"hasGnuplotSupport", &IndexMustache::hasGnuplotSupport},
    });
  }

  mstch::node IndexMustache::hasGnuplotSupport() noexcept
  {
    //DLog(" -> IndexMustache::hasGnuplotSupport()\n");

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    return true;
#else
    return false;
#endif
  }
} // Wallet::Mustache Namespace

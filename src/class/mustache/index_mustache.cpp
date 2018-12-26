
#include "debug.hpp"
#include "config.hpp"
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
#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> IndexMustache::hasGnuplotSupport() YES\n");
    return true;
#else
    DLog(" -> IndexMustache::hasGnuplotSupport() NO\n");
    return false;
#endif
  }
} // Wallet::Mustache Namespace

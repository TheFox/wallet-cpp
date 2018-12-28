
#ifndef WALLETCPP_MUSTACHE_BASE_GNUPLOT_HPP_
#define WALLETCPP_MUSTACHE_BASE_GNUPLOT_HPP_

#ifdef __has_include
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

namespace Wallet::Mustache
{
  class BaseGnuplot : public mstch::object
  {
  public:
    // Constructor
    BaseGnuplot();
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_BASE_GNUPLOT_HPP_

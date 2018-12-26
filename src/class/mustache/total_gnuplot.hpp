
#ifndef WALLETCPP_MUSTACHE_TOTAL_GNUPLOT_HPP_
#define WALLETCPP_MUSTACHE_TOTAL_GNUPLOT_HPP_

#include <string>

#include "base_gnuplot.hpp"

namespace Wallet::Mustache
{
  class TotalGnuplot final : public BaseGnuplot
  {
  public:
    // Constructor
    TotalGnuplot(std::string, std::string);

  private:
    // Functions
    mstch::node getPngFilePath() noexcept;
    mstch::node getDatFilePath() noexcept;

    // Properties
    const std::string pngFilePath{};
    const std::string datFilePath{};
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_TOTAL_GNUPLOT_HPP_

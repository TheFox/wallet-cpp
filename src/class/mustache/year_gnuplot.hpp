
#ifndef WALLETCPP_MUSTACHE_YEAR_GNUPLOT_HPP_
#define WALLETCPP_MUSTACHE_YEAR_GNUPLOT_HPP_

#include <string>

#include "base_gnuplot.hpp"

namespace Wallet::Mustache
{
  class YearGnuplot final : public BaseGnuplot
  {
  public:
    // Constructor
    YearGnuplot(std::string, std::string, std::string);

  private:
    // Properties
    const std::string year{};
    const std::string pngFilePath{};

    const std::string datFilePath{};

    // Functions
    mstch::node getYear();
    mstch::node getPngFilePath() noexcept;
    mstch::node getDatFilePath() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_YEAR_GNUPLOT_HPP_

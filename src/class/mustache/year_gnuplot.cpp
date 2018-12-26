
#include "debug.hpp"
#include "year_gnuplot.hpp"

namespace Wallet::Mustache
{
  YearGnuplot::YearGnuplot(std::string _year, std::string _pngFilePath, std::string _dat) :
    year{std::move(_year)}, pngFilePath{std::move(_pngFilePath)}, datFilePath{std::move(_dat)}
  {
    DLog(" -> YearGnuplot::YearGnuplot()\n");

    this->register_methods(this, {
      {"year",          &YearGnuplot::getYear},
      {"png_file_path", &YearGnuplot::getPngFilePath},
      {"dat_file_path", &YearGnuplot::getDatFilePath},
    });
  }

  mstch::node YearGnuplot::getYear()
  {
    return this->year;
  }

  mstch::node YearGnuplot::getPngFilePath() noexcept
  {
    //DLog(" -> YearGnuplot::getPngFilePath()\n");
    return this->pngFilePath;
  }

  mstch::node YearGnuplot::getDatFilePath() noexcept
  {
    //DLog(" -> YearGnuplot::getDatFilePath()\n");
    return this->datFilePath;
  }
} // Wallet::Mustache Namespace

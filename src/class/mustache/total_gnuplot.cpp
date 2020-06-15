
#include "debug.hpp"
#include "total_gnuplot.hpp"

namespace Wallet::Mustache
{
  TotalGnuplot::TotalGnuplot(std::string _pngFilePath, std::string _datFilePath) :
    pngFilePath(std::move(_pngFilePath)), datFilePath(std::move(_datFilePath))
  {
    //DLog("-> TotalGnuplot::TotalGnuplot('%s', '%s')\n", _pngFilePath.c_str(), _datFilePath.c_str());

    this->register_methods(this, {
      {"png_file_path", &TotalGnuplot::getPngFilePath},
      {"dat_file_path", &TotalGnuplot::getDatFilePath},
    });
  }

  mstch::node TotalGnuplot::getPngFilePath() noexcept
  {
    //DLog("-> TotalGnuplot::getPngFilePath()\n");
    return this->pngFilePath;
  }

  mstch::node TotalGnuplot::getDatFilePath() noexcept
  {
    //DLog("-> TotalGnuplot::getDatFilePath()\n");
    return this->datFilePath;
  }
} // Wallet::Mustache Namespace

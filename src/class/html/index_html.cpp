
#include <memory> // make_shared

#include "debug.hpp"
#include "config.hpp"
#include "index_html.hpp"
#include "components.hpp"

namespace Wallet::Html
{
  IndexMustacheObject::IndexMustacheObject(mstch::array _entries, mstch::map _total) :
    BaseMustacheObject(std::move(_entries), std::move(_total))
  {
    //DLog(" -> IndexMustacheObject::IndexMustacheObject()\n");

    this->register_methods(this, {
      {"hasGnuplotSupport", &IndexMustacheObject::hasGnuplotSupport},
    });
  }

  mstch::node IndexMustacheObject::hasGnuplotSupport() noexcept
  {
    DLog(" -> IndexMustacheObject::hasGnuplotSupport()\n");

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    return true;
#else
    return false;
#endif
  }

  TotalGnuplotObject::TotalGnuplotObject(std::string _pngFilePath, std::string _datFilePath) :
    pngFilePath(std::move(_pngFilePath)), datFilePath(std::move(_datFilePath))
  {
    DLog(" -> TotalGnuplotObject::TotalGnuplotObject('%s', '%s')\n", _pngFilePath.c_str(), _datFilePath.c_str());

    this->register_methods(this, {
      {"png_file_path", &TotalGnuplotObject::getPngFilePath},
      {"dat_file_path", &TotalGnuplotObject::getDatFilePath},
    });
  }

  mstch::node TotalGnuplotObject::getPngFilePath() noexcept
  {
    DLog(" -> TotalGnuplotObject::getPngFilePath()\n");

    return this->pngFilePath;
  }

  mstch::node TotalGnuplotObject::getDatFilePath() noexcept
  {
    DLog(" -> TotalGnuplotObject::getDatFilePath()\n");

    return this->datFilePath;
  }

  IndexHtml::IndexHtml(fs::path _basePath, fs::path _tmpPath) :
    BaseHtml{std::move(_basePath), std::move(_tmpPath), fs::path{"index.html"}, "Index"}
  {
    //DLog(" -> IndexHtml::IndexHtml('%s')\n", this->basePath.c_str());
  }

  void IndexHtml::addRow(const IndexHtmlRow row) noexcept
  {
    //DLog(" -> IndexHtml::addRow(%s)\n", row.year.c_str());

    const mstch::map rowMap{
      {"year",              row.year},
      {"revenue",           row.revenue},
      {"expense",           row.expense},
      {"balance",           row.balance},
      {"balance_class",     row.balanceClass},
      {"balance_sum",       row.balanceSum},
      {"balance_sum_class", row.balanceSumClass},
    };
    this->entries.push_back(rowMap);
  }

  void IndexHtml::generate(const IndexHtmlRow totalRow) const
  {
    DLog(" -> IndexHtml::generate('%s')\n", totalRow.year.c_str());

    if (!fs::exists(WALLETCPP_INDEX_VIEW_PATH)) {
      DLog("ERROR: Index template file does not exists: '%s'\n", WALLETCPP_INDEX_VIEW_PATH);
      throw std::string{"Index template file does not exists: "} + WALLETCPP_INDEX_VIEW_PATH;
    }
#ifdef WALLETCPP_GNUPLOT_SUPPORT
    if (!fs::exists(WALLETCPP_TOTAL_GNUPLOT_PATH)) {
      DLog("ERROR: Gnuplot total template file does not exists: '%s'\n", WALLETCPP_TOTAL_GNUPLOT_PATH);
      throw std::string{"Gnuplot total template file does not exists: "} + WALLETCPP_TOTAL_GNUPLOT_PATH;
    }
#endif

    // Total
    const mstch::map total{
      {"label",         totalRow.year},
      {"revenue",       totalRow.revenue},
      {"expense",       totalRow.expense},
      {"balance",       totalRow.balance},
      {"balance_class", totalRow.balanceClass},
    };

    const std::string tpl = Components::readFileIntoString(WALLETCPP_INDEX_VIEW_PATH);
    const auto context = std::make_shared<IndexMustacheObject>(this->entries, total);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> YearHtml::generate() -> GNUPlot support\n");

    const auto pngFilePath = (this->basePath / "total.png").string();
    const auto datFilePath = (this->tmpPath / "total.dat").string();

    const std::string gnuplotTpl = Components::readFileIntoString(WALLETCPP_TOTAL_GNUPLOT_PATH);
    const auto gnuplotContext = std::make_shared<TotalGnuplotObject>(pngFilePath, datFilePath);

    // Output: total.gp
    const auto gnuplotFilePath = (this->tmpPath / "total.gp").string();
    std::ofstream totalFh{gnuplotFilePath};
    totalFh << mstch::render(gnuplotTpl, gnuplotContext);
    totalFh.close();
#endif
  }
} // Wallet::Html Namespace

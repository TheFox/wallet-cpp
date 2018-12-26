
#include <memory> // make_shared

#include "debug.hpp"
#include "config.hpp"
#include "index_html.hpp"
#include "components.hpp"
#include "class/mustache/index_mustache.hpp"
#ifdef WALLETCPP_GNUPLOT_SUPPORT
#  include "class/mustache/total_gnuplot.hpp"
#endif

namespace Wallet::Html
{
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
    //DLog(" -> IndexHtml::generate('%s')\n", totalRow.year.c_str());

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
    const auto context = std::make_shared<Mustache::IndexMustache>(this->entries, total);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> YearHtml::generate() -> GNUPlot support\n");

    const auto pngFilePath = (this->basePath / "total.png").string();
    const auto datFilePath = (this->tmpPath / "total.dat").string();

    const std::string gnuplotTpl = Components::readFileIntoString(WALLETCPP_TOTAL_GNUPLOT_PATH);
    const auto gnuplotContext = std::make_shared<Mustache::TotalGnuplot>(pngFilePath, datFilePath);

    // Output: total.gp
    const auto gnuplotFilePath = (this->tmpPath / "total.gp").string();
    std::ofstream totalFh{gnuplotFilePath};
    totalFh << mstch::render(gnuplotTpl, gnuplotContext);
    totalFh.close();

    const auto gnuplotCmd = std::string{"x"} + "y";
    DLog(" -> exec gnuplot: '%s'\n", gnuplotCmd.c_str());
#endif
  }
} // Wallet::Html Namespace

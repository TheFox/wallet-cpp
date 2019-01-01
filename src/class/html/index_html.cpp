
#include <memory> // make_shared
#include <algorithm> // transform, accumulate
#include <iterator> // back_inserter, ostream_iterator
#include <sstream> // ostringstream
#include <fstream> // ofstream
#include <cstdlib> // system

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

  void IndexHtml::addRow(IndexHtmlRow row) noexcept
  {
    //DLog(" -> IndexHtml::addRow(%s)\n", row.year.c_str());
    this->log("[index_html] add row: " + row.year);

    this->entries.push_back(std::move(row));
  }

  void IndexHtml::generate(const IndexHtmlRow totalRow) const
  {
    DLog(" -> IndexHtml::generate('%s')\n", totalRow.year.c_str());
    this->log("[index_html] generate");

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

    // Transform IndexHtmlRow entries to mstch::array<mstch::map>.
    mstch::array _entries{};
    std::transform(this->entries.cbegin(), this->entries.cend(), std::back_inserter(_entries), [](auto row) {
      //DLog(" -> transform\n");

      return mstch::map{
        {"year",              std::move(row.year)},
        {"revenue",           std::move(row.revenue)},
        {"expense",           std::move(row.expense)},
        {"balance",           std::move(row.balance)},
        {"balance_class",     std::move(row.balanceClass)},
        {"balance_sum",       std::move(row.balanceSum)},
        {"balance_sum_class", std::move(row.balanceSumClass)},
      };
    });

    // Total
    const mstch::map total{
      {"label",         totalRow.year},
      {"revenue",       totalRow.revenue},
      {"expense",       totalRow.expense},
      {"balance",       totalRow.balance},
      {"balance_class", totalRow.balanceClass},
    };

    const auto tpl = Components::readFileIntoString(WALLETCPP_INDEX_VIEW_PATH);
    const auto context = std::make_shared<Mustache::IndexMustache>(_entries, total);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> len: %lu\n", this->entries.size());

    const auto maxLen = this->entries.size() >= 10 ? this->entries.size() - 10 : 0;
    const auto entriesBegin = this->entries.cbegin() + maxLen;
    const auto entriesEnd = this->entries.cend();

    std::vector<std::string> datRows{};
    std::transform(entriesBegin, entriesEnd, std::back_inserter(datRows), [](const auto& entry) {
      std::string row{entry.year};
      row += " " + (entry.revenue.empty() ? "0" : entry.revenue);
      row += " " + (entry.expense.empty() ? "0" : entry.expense);
      row += " " + (entry.balance.empty() ? "0" : entry.balance);
      row += " " + (entry.balanceSum.empty() ? "0" : entry.balanceSum);

      return row;
    });

    // Write data file for GNUPlot.
    const auto datFilePath = (this->tmpPath / "total.dat").string();
    DLog(" -> dat: '%s'\n", datFilePath.c_str());
    std::ofstream datFh{datFilePath};
    std::copy(datRows.cbegin(), datRows.cend(), std::ostream_iterator<std::string>(datFh, "\n"));
    datFh.close();

    // PNG file
    const auto pngFilePath = (this->basePath / "total.png").string();
    DLog(" -> png: '%s'\n", pngFilePath.c_str());

    // Mustache Template file
    const auto gnuplotTpl = Components::readFileIntoString(WALLETCPP_TOTAL_GNUPLOT_PATH);

    // Mustache Context
    const auto gnuplotContext = std::make_shared<Mustache::TotalGnuplot>(pngFilePath, datFilePath);

    // Total Gnuplot File
    const auto gnuplotFilePath = (this->tmpPath / "total.gp").string();
    DLog(" -> gp: '%s'\n", gnuplotFilePath.c_str());
    std::ofstream totalFh{gnuplotFilePath};
    totalFh << mstch::render(gnuplotTpl, gnuplotContext);
    totalFh.close();

    // Run GNUPlot
    const auto gnuplotCmd = std::string{"gnuplot "} + gnuplotFilePath + " &> /dev/null < /dev/null";

#ifdef DEBUG
    DLog(" -> exec gnuplot: '%s'\n", gnuplotCmd.c_str());
    const auto execrv = std::system(gnuplotCmd.c_str());
    DLog(" -> exec gnuplot: %d\n", execrv);
#else
    std::system(gnuplotCmd.c_str());
#endif
#endif
  }
} // Wallet::Html Namespace

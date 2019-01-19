
#include <iomanip> // setprecision
#include <ios> // fixed
#include <sstream> // ostringstream

#include "debug.hpp"
#include "config.hpp"
#include "html_generator.hpp"
#include "index_html.hpp"
#include "year_html.hpp"

namespace Wallet::Html
{
  HtmlGenerator::HtmlGenerator(fs::path _basePath, fs::path _tmpPath, Wallet::Container::EntryContainer _container) :
    yearPath(_basePath / "year"), basePath(std::move(_basePath)), tmpPath(std::move(_tmpPath)),
    container(std::move(_container))
  {
    //DLog(" -> HtmlGenerator::HtmlGenerator(%s, %p)\n", this->basePath.c_str(), &this->container);
  }

  void HtmlGenerator::generate() const
  {
    DLog(" -> HtmlGenerator::generate()\n");

    // Setup
    this->setup();

    // Balance Sum
    Accountable::Number balanceSum{0.0};

    // Index HTML
    IndexHtml indexHtml{this->basePath, this->tmpPath};
    indexHtml.logLevel = this->logLevel;

    // Iterate Years.
    for (const auto& yearPair : container.years) {
      //DLog(" -> year: %d\n", yearPair.first);

      const auto yearStr = std::to_string(yearPair.first);
      this->log("[html_generator] year: " + yearStr);

      // Create Directory
      const auto yearDirPath = this->yearPath / yearStr;
      if (!fs::exists(yearDirPath)) {
        fs::create_directories(yearDirPath);
      }

      const YearHtml yearHtml{yearDirPath, this->tmpPath, yearPair.second};
      yearHtml.generate();

      // Balance Sum
      balanceSum += yearPair.second.balance;

      // Balance Sum String
      std::ostringstream balanceSumSs{};
      balanceSumSs << std::fixed << std::setprecision(2) << balanceSum;

      // Add row to HTML file.
      const IndexHtmlRow row{
        yearStr,
        yearPair.second.getRevenueStr(),
        yearPair.second.getExpenseStr(),
        yearPair.second.getBalanceStr(),
        yearPair.second.getBalanceHtmlClass(),
        balanceSumSs.str(),
        balanceSum < 0 ? "red" : ""
      };
      indexHtml.addRow(row);
    }

    // Generate HTML file.
    const IndexHtmlRow totalRow{
      "TOTAL",
      container.getRevenueStr(),
      container.getExpenseStr(),
      container.getBalanceStr()
    };
    indexHtml.generate(totalRow);
  }

  void HtmlGenerator::setup() const noexcept
  {
    this->log("[html_generator] setup");

    // Make tmp/ directory.
    if (!fs::exists(this->tmpPath)) {
      fs::create_directories(this->tmpPath);
    }

    if (!fs::exists(this->basePath)) {
      fs::create_directory(this->basePath);
    }
    if (!fs::exists(this->yearPath)) {
      fs::create_directory(this->yearPath);
    }

#ifdef NDEBUG
    this->log("[html_generator] copy file: " PROJECT_RESOURCES_PREFIX);
    fs::copy_file(fs::path{PROJECT_RESOURCES_PREFIX} / "css/style.css",
      this->basePath / "style.css", fs::copy_option::overwrite_if_exists);
#endif
  }
} // Wallet::Html Namespace

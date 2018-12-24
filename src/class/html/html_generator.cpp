
#include <iomanip> // setprecision
#include <ios> // fixed

#include "debug.hpp"
#include "config.hpp"
#include "html_generator.hpp"
#include "index_html.hpp"
#include "year_html.hpp"

namespace Wallet::Html
{
  HtmlGenerator::HtmlGenerator(fs::path _basePath, Wallet::Container::EntryContainer _container) :
    yearPath(_basePath / "year"), basePath(std::move(_basePath)), container(std::move(_container))
  {
    //DLog(" -> HtmlGenerator::HtmlGenerator(%s, %p)\n", this->basePath.c_str(), &this->container);
  }

  void HtmlGenerator::generate() const noexcept
  {
    DLog(" -> HtmlGenerator::generate()\n");

    // Setup
    this->setup();

    // Balance Sum
    Accountable::Number balanceSum{0.0};

    // Index HTML
    IndexHtml indexHtml{this->basePath};

    // Iterate Years.
    for (const auto& yearPair : container.years) {
      //DLog(" -> year: %d\n", yearPair.first);

      const auto yearStr = std::to_string(yearPair.first);

      // Create Directory
      const auto yearDirPath = this->yearPath / yearStr;
      if (!fs::exists(yearDirPath)) {
        fs::create_directories(yearDirPath);
      }

      YearHtml yearHtml{yearDirPath, yearPair.second};
      yearHtml.generate();

      // Balance Sum
      balanceSum += yearPair.second.balance;

      // Balance Sum String
      std::stringstream balanceSumSs;
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
    using fs::exists;
    using fs::create_directory;

    if (!exists(this->basePath)) {
      fs::create_directory(this->basePath);
    }
    if (!exists(this->yearPath)) {
      fs::create_directory(this->yearPath);
    }

#ifdef NDEBUG
    fs::copy_file(fs::path{PROJECT_SHARE_RESOURCES_DIR} / "css/style.css",
      this->basePath / "style.css", fs::copy_option::overwrite_if_exists);
#endif
  }
} // Wallet::Html Namespace

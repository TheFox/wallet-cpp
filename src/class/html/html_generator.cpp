
#include <iomanip> // setprecision
#include <ios> // fixed

#include "html_generator.hpp"
#include "../../debug.hpp"
#include "index_html.hpp"
#include "year_html.hpp"

namespace Wallet { namespace Html
{
  HtmlGenerator::HtmlGenerator(boost::filesystem::path _basePath, Wallet::Container::EntryContainer _container) :
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
    AccountAble::Number balanceSum{0.0};

    // Index HTML
    IndexHtml indexHtml{this->basePath};

    // Iterate Years.
    for (const auto& yearPair : container.years) {
      //DLog(" -> year: %d\n", yearPair.first);

      const auto yearStr = std::to_string(yearPair.first);

      // Create Directory
      const auto yearDirPath = this->yearPath / yearStr;
      if (!boost::filesystem::exists(yearDirPath)) {
        boost::filesystem::create_directories(yearDirPath);
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
        balanceSumSs.str()
      };
      indexHtml.addRow(row);
    }

    // Generate HTML file.
    const IndexHtmlRow row{
      container.getRevenueStr(),
      container.getExpenseStr(),
      container.getBalanceStr()
    };
    indexHtml.generate(row);
  }

  void HtmlGenerator::setup() const noexcept
  {
    using boost::filesystem::exists;
    using boost::filesystem::create_directory;

    if (!exists(this->basePath)) {
      boost::filesystem::create_directory(this->basePath);
    }
    if (!exists(this->yearPath)) {
      boost::filesystem::create_directory(this->yearPath);
    }
  }
}} // Wallet::Html Namespace

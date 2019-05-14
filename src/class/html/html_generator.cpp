
#include <iomanip> // setprecision
#include <ios> // fixed
#include <sstream> // ostringstream
#include <algorithm> // transform

#ifdef __has_include
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

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
    Trait::Accountable::Number balanceSum{0.0};

    // Index HTML
    IndexHtml indexHtml{this->basePath, this->tmpPath};
    indexHtml.logLevel = this->logLevel;

    // Epics
    const auto _epics_begin = this->container.epics.begin();
    const auto _epics_end   = this->container.epics.end();

    // Iterate Years.
    for (const auto& yearPair : this->container.years) {
      //DLog(" -> year: %d\n", yearPair.first);

      const auto yearStr = std::to_string(yearPair.first);
      this->log("[html_generator] year: " + yearStr);

      // Create Directory
      const auto yearDirPath = this->yearPath / yearStr;
      if (!fs::exists(yearDirPath)) {
        fs::create_directories(yearDirPath);
      }

      // Generate Year HTML file.
      const YearHtml yearHtml{yearDirPath, this->tmpPath, yearPair.second};
      yearHtml.generate();

      // Balance Sum
      balanceSum += yearPair.second.balance;

      // Balance Sum String
      std::ostringstream balanceSumSs{};
      balanceSumSs << std::fixed << std::setprecision(2) << balanceSum;

      // Year Epics
      // Match common epics to year epics.
      mstch::array _epics{};
      /*for (const auto& epicPair : yearPair.second.epics) {
        DLog(" -> HtmlGenerator::generate() -> epic pair: %s (%s)\n",
          epicPair.first.c_str(), epicPair.second.epic.title.c_str());
        
        mstch::map _emap{
            {"handle", epicPair.second.epic.handle},
            {"title", epicPair.second.epic.title},
            {"bg_color", epicPair.second.epic.bgColor},
            {"epic_balance", epicPair.second.getBalanceStr()},
            {"epic_balance_class", epicPair.second.getBalanceHtmlClass()},
        };
        _epics.push_back(_emap);
      }*/
      
      // TODO
      /*std::transform(_epics_begin, _epics_end, std::back_inserter(_epics), [](const auto& pair){
        DLog(" -> HtmlGenerator::generate() -> epic pair\n");
        // DLog(" -> HtmlGenerator::generate() -> epic pair: %s\n", epicPair.first.c_str());

        try {
          // Search by handle.
          DLog(" -> HtmlGenerator::generate() -> search by handle\n");
        }
        catch (const std::out_of_range& exception) {
          DLog(" -> HtmlGenerator::generate() -> error\n");
        }
      });*/

      // Add row to HTML file.
      const IndexHtmlRow row{
        yearStr,
        yearPair.second.getRevenueStr(),
        yearPair.second.getExpenseStr(),
        yearPair.second.getBalanceStr(),
        yearPair.second.getBalanceHtmlClass(),
        balanceSumSs.str(),
        balanceSum < 0 ? "red" : "",
        // _epics
      };
      indexHtml.addRow(row);
    } // this->container.years

    // Total Epics
    mstch::array totalEpics{};
    std::transform(_epics_begin, _epics_end, std::back_inserter(totalEpics), [](const auto& epicPair) {
      // DLog(" -> HtmlGenerator::generate() -> transform epic: %s/%s -> '%s'\n",
      //   epicPair.first.c_str(), epicPair.second.epic.handle.c_str(),
      //   epicPair.second.epic.title.c_str());

      // second = EpicContainer
      return mstch::map{
        {"epic_title", epicPair.second.epic.title},
        {"epic_balance", epicPair.second.getBalanceStr()},
        {"epic_balance_class", epicPair.second.getBalanceHtmlClass()},
      };
    });

    // Total Row
    const IndexHtmlRow totalRow{
      "TOTAL", // year
      container.getRevenueStr(), // revenue
      container.getExpenseStr(), // expense
      container.getBalanceStr(), // balance
      std::string{}, // balanceClass
      std::string{}, // balanceSum
      std::string{}  // balanceSumClass
      // totalEpics
    };

    // Generate HTML file.
    indexHtml.generate(totalRow, this->container.epics);
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

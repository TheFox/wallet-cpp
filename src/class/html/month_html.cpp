
#include <fstream> // ofstream
#include <iomanip> // setprecision, setfill, setw
#include <iterator> // back_inserter
#include <algorithm> // transform
//#include <sstream> // ostringstream
#include <cstdint> // uint8_t

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace calendar = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

#include "debug.hpp"
#include "config.hpp"
#include "month_html.hpp"
#include "components.hpp"
#include "class/mustache/month_mustache.hpp"

namespace Wallet::Html
{
  MonthHtml::MonthHtml(fs::path _basePath, MonthPair _map, const SortedEpicPtrs& _epicPtrs) :
  //MonthHtml::MonthHtml(fs::path _basePath, MonthPair _map, UnsortedEpics _epics, SortedEpicPtrs _epicPtrs) :
      BaseHtml{std::move(_basePath), fs::path{}, fs::path{getMonthFile(_map.first)},
          getMonthName(_map.first) + " " + std::to_string(_map.second.year)}, // BaseHtml
      name(getMonthName(_map.first)), container(std::move(_map.second)), year(
      std::to_string(_map.second.year)), epicPtrs(_epicPtrs)
  {
    DLog("-> MonthHtml::MonthHtml()\n");
    //DLog("-> MonthHtml::MonthHtml(bp'%s') -> p'%s' n'%s'\n", this->basePath.c_str(),
    //  this->getFileName().c_str(), this->name.c_str());
    //this->epicPtrs = _epicPtrs;
    //this->epicPtrs = std::move(_epicPtrs);
  }

  void MonthHtml::generate() const
  {
    DLog("-> MonthHtml::generate() -> %d %s\n", this->container.year, this->name.c_str());

    const auto yearStr = std::to_string(this->container.year);

    this->log("[month_html] generate: " + yearStr);

    if (!fs::exists(WALLETCPP_MONTH_VIEW_PATH)) {
      DLog("ERROR: Month template file does not exists: '%s'\n", WALLETCPP_MONTH_VIEW_PATH);
      throw std::string{"Month template file does not exists: "} + WALLETCPP_MONTH_VIEW_PATH;
    }

    // Table Body
    mstch::array entries{};

    // Columns
    bool showCategories = false;
    bool showEpics = false;
    bool showComments = false;

    SortedEpicPtrs _epicPtrs = this->epicPtrs;

    std::uint64_t entryCount{};
    for (const auto& dayPair : this->container.days) {
      //DLog("-> MonthHtml::generate() -> day pair\n");

      const auto _begin = dayPair.second.entries.cbegin();
      const auto _end = dayPair.second.entries.cend();

      // Add Day entries to month entry list.
      std::transform(_begin, _end, std::back_inserter(entries),
          [&entryCount, &showCategories, &showEpics, &showComments, &_epicPtrs](const auto& entry) {
            //DLog("-> MonthHtml::generate() -> day pair -> transform entry (%c) '%s'\n", showEpics ? 'Y' : 'N', entry.epicHandle.c_str());

            // Count
            entryCount++;

            // Show Categories Column
            if (!showCategories && !entry.hasDefaultCategory()) {
              showCategories = true;
            }

            // Show Epics Column
            if (!showEpics && !entry.hasDefaultEpic()) {
              showEpics = true;
            }

            if (!showComments && !entry.comment.empty()) {
              showComments = true;
            }

            const auto epicPtr = _epicPtrs[entry.epicHandle];

            std::string epicHandle{};
            std::string epicTitle{};
            std::string epicBgColor{};
            if (epicPtr == nullptr) {
              Epic defaultEpic{};
              epicHandle = defaultEpic.handle;
              epicTitle = defaultEpic.title;
              epicBgColor = defaultEpic.bgColor;
            } else {
              epicHandle = epicPtr->handle;
              epicTitle = epicPtr->title;
              epicBgColor = epicPtr->bgColor;
              //DLog("-> MonthHtml::generate() -> epic ptr '%s'\n", epicHandle.c_str());
            }

            return mstch::map{
                {"no",            std::to_string(entryCount)},
                {"date",          entry.getDateStr()},
                {"title",         entry.title},

                {"revenue",       entry.getRevenueStr()},
                {"expense",       entry.getExpenseStr()},
                {"balance",       entry.getBalanceStr()},
                {"balance_class", entry.getBalanceHtmlClass()},

                {"category",      entry.getCategoryHtml()},

                {"epic_handle",   std::move(epicHandle)},
                {"epic_title",    std::move(epicTitle)},
                {"epic_bg_color", std::move(epicBgColor)},

                {"comment",       entry.comment},
            };
          }); // Transform Entries
    } // this->container.days

    // Columns
    const std::uint8_t columns = showCategories + showEpics + showComments;
    const auto columnsStr = std::to_string(columns);
    DLog("-> MonthHtml::generate() -> columns: %d -> '%s'\n", columns, columnsStr.c_str());

    const mstch::map total{
        {"label",           std::string{"TOTAL"}},
        {"revenue",         this->container.getRevenueStr()},
        {"revenue_percent", this->container.getRevenuePercentStr()},
        {"expense",         this->container.getExpenseStr()},
        {"expense_percent", this->container.getExpensePercentStr()},
        {"balance",         this->container.getBalanceStr()},
        {"balance_class",   this->container.getBalanceHtmlClass()},
        {"has_columns",     columns > 0},
        {"columns",         columnsStr},
    };

    const auto tpl = Components::readFileIntoString(WALLETCPP_MONTH_VIEW_PATH);
    const auto context = std::make_shared<Mustache::MonthMustache>("../..", entries, total, yearStr, this->name,
        this->container.fileName, showCategories, showEpics, showComments);

    // Month HTML File Output
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context) << '\n';
    indexFh.close();
  }

  std::string MonthHtml::getMonthFile(const Container::Month _month) noexcept
  {
    std::ostringstream ss{};
    ss << "month_";
    ss << std::setfill('0') << std::setw(2) << std::to_string(_month);
    ss << ".html";
    return ss.str();
  }

  std::string MonthHtml::getMonthName(const Container::Month _month) noexcept
  {
    calendar::greg_month month{_month};
    return month.as_long_string();
  }
} // Wallet::Html Namespace

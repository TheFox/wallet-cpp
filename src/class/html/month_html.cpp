
#include <fstream> // ofstream
#include <iomanip> // setprecision, setfill, setw
#include <iterator> // back_inserter
#include <algorithm> // transform
#include <sstream> // ostringstream

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
  MonthHtml::MonthHtml(fs::path _basePath, Container::MonthPair _map, Container::Epics _epics) :
    BaseHtml{std::move(_basePath), fs::path{}, fs::path{getMonthFile(_map.first)},
      getMonthName(_map.first) + " " + std::to_string(_map.second.year)}, // BaseHtml
    name(getMonthName(_map.first)), container(std::move(_map.second)), year(std::to_string(_map.second.year)), epics(std::move(_epics))
  {
    //DLog(" -> MonthHtml::MonthHtml(bp'%s') -> p'%s' n'%s'\n", this->basePath.c_str(),
    //  this->getFileName().c_str(), this->name.c_str());
  }

  void MonthHtml::generate() const
  {
    DLog(" -> MonthHtml::generate()\n");

    const auto yearStr = std::to_string(this->container.year);

    this->log("[month_html] generate: " + yearStr);

    if (!fs::exists(WALLETCPP_MONTH_VIEW_PATH)) {
      DLog("ERROR: Month template file does not exists: '%s'\n", WALLETCPP_MONTH_VIEW_PATH);
      throw std::string{"Month template file does not exists: "} + WALLETCPP_MONTH_VIEW_PATH;
    }

    // Table Body
    mstch::array entries{};

    // Columns
    bool showEpics = false;

    Container::Epics _epics = this->epics;
    //const auto& _epics = this->epics;

    std::uint64_t entryCount{};
    for (const auto& dayPair : this->container.days) {
      //DLog("     -> day pair\n");

      const auto _begin = dayPair.second.entries.cbegin();
      const auto _end = dayPair.second.entries.cend();

      // Add Day entries to month entry list.
      std::transform(_begin, _end, std::back_inserter(entries), [&entryCount, &showEpics, &_epics](const auto& entry) {
        ++entryCount;

        if (!showEpics && !entry.hasDefaultEpic())
          showEpics = true;

        //const auto& epic = this->epics[entry.handle];
        const auto& epic = _epics[entry.epicHandle];
        //DLog(" -> MonthHtml::generate() -> epic '%s'\n", epic.handle.c_str());

        return mstch::map{
          {"no",            std::to_string(entryCount)},
          {"date",          entry.getDateStr()},
          {"title",         entry.title},
          {"revenue",       entry.getRevenueStr()},
          {"expense",       entry.getExpenseStr()},
          {"balance",       entry.getBalanceStr()},
          {"balance_class", entry.getBalanceHtmlClass()},
          {"category",      entry.getCategoryHtml()},
          {"epic_handle",   entry.getEpicHandleHtml()},
          {"epic_title",    epic.title},
          {"epic_bg_color", epic.bgColor},
          {"comment",       entry.comment},
        };
      });
    } // this->container.days

    const mstch::map total{
      {"label",         std::string{"TOTAL"}},
      {"revenue",       this->container.getRevenueStr()},
      {"expense",       this->container.getExpenseStr()},
      {"balance",       this->container.getBalanceStr()},
      {"balance_class", this->container.getBalanceHtmlClass()},
    };

    const auto tpl = Components::readFileIntoString(WALLETCPP_MONTH_VIEW_PATH);
    const auto context = std::make_shared<Mustache::MonthMustache>("../..", entries, total, yearStr, this->name,
      this->container.fileName, showEpics);

    // Month HTML File Output
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context) << '\n';
    indexFh.close();
  }

  std::string MonthHtml::getMonthFile(const Container::ContainerMonth _month) noexcept
  {
    std::ostringstream ss{};
    ss << "month_";
    ss << std::setfill('0') << std::setw(2) << std::to_string(_month);
    ss << ".html";
    return ss.str();
  }

  std::string MonthHtml::getMonthName(const Container::ContainerMonth _month) noexcept
  {
    calendar::greg_month month{_month};
    return month.as_long_string();
  }
} // Wallet::Html Namespace

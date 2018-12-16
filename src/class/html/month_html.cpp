
#include <fstream> // ofstream
#include <iomanip> // setprecision, setfill, setw

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace calendar = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#endif // __has_include

#include "month_html.hpp"
#include "../../debug.hpp"

namespace Wallet::Html
{
  MonthHtml::MonthHtml(fs::path _basePath, Container::MonthPair _map) :
    BaseHtml{std::move(_basePath), fs::path{getMonthFile(_map.first)}, getMonthName(_map.first) + " " + std::to_string(_map.second.year)},
    name(getMonthName(_map.first)), container(std::move(_map.second)), year(std::to_string(_map.second.year))
  {
    DLog(" -> MonthHtml::MonthHtml(bp'%s') -> p'%s' n'%s'\n", this->getBasePath().c_str(),
      this->getFileName().c_str(), this->name.c_str());
  }

  void MonthHtml::generate() const noexcept
  {
    DLog(" -> YearHtml::generate()\n");

    //for (const auto& dayPair : monthContainer.days) {
    //  DLog("     -> day pair\n");
    //  this->htmlOutputDay(dayPair.second);
    //}

    // Month Doc
    auto monthDoc = this->getHtmlDoc("../../index.html");
    monthDoc.AppendNodeToBody(
      CTML::Node{"h2"}.AppendText("Month: " + this->name + " ").AppendChild(CTML::Node{"a", this->year}.SetAttribute("href", "index.html")));
    //monthDoc.AppendNodeToBody(monthTable);

    // Month File Output
    DLog("     -> write month file: %s\n", this->getFullPath().c_str());
    std::ofstream monthFh{};
    monthFh.open(this->getFullPath(), std::ofstream::out);
    monthFh << monthDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    monthFh.close();
  }

  std::string MonthHtml::getMonthFile(const Container::ContainerMonth month) noexcept
  {
    std::stringstream ss{};
    ss << "month_";
    ss << std::setfill('0') << std::setw(2) << std::to_string(month);
    ss << ".html";
    return ss.str();
  }

  std::string MonthHtml::getMonthName(const Container::ContainerMonth _month) noexcept
  {
    calendar::greg_month month{_month};
    return month.as_long_string();
  }
}

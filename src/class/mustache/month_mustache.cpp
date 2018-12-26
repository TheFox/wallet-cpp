
#include "debug.hpp"
#include "month_mustache.hpp"

namespace Wallet::Mustache
{
  MonthMustache::MonthMustache(std::string _rel, mstch::array _entries, mstch::map _total,
                               std::string _year, std::string _month, std::string _fileName) :
    BaseMustache{std::move(_rel), std::move(_entries), std::move(_total)},
    year{std::move(_year)}, month{std::move(_month)}, fileName{std::move(_fileName)}
  {
    //DLog(" -> MonthMustache::MonthMustache()\n");

    this->register_methods(this, {
      {"year",      &MonthMustache::getYear},
      {"month",     &MonthMustache::getMonth},
      {"file_name", &MonthMustache::getFileName},
    });
  }

  mstch::node MonthMustache::getYear() noexcept
  {
    //DLog(" -> MonthMustache::getYear()\n");
    return this->year;
  }

  mstch::node MonthMustache::getMonth() noexcept
  {
    //DLog(" -> MonthMustache::getMonth()\n");
    return this->month;
  }

  mstch::node MonthMustache::getFileName() noexcept
  {
    //DLog(" -> MonthMustache::getFileName()\n");
    return this->fileName;
  }
} // Wallet::Mustache Namespace

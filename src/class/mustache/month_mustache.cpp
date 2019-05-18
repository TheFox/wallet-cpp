
#include "debug.hpp"
#include "month_mustache.hpp"

namespace Wallet::Mustache
{
  MonthMustache::MonthMustache(std::string _rel, mstch::array _entries, mstch::map _total,
                               std::string _year, std::string _month, std::string _fileName, bool _showCategories,
                               bool _showEpics, bool _showComments) :
      BaseMustache{std::move(_rel), std::move(_entries), std::move(_total)},
      year(std::move(_year)), month(std::move(_month)), fileName(std::move(_fileName)), showCategories(
      _showCategories), showEpics(_showEpics), showComments(_showComments)
  {
    //DLog(" -> MonthMustache::MonthMustache()\n");

    this->register_methods(this, {
        {"year",            &MonthMustache::getYear},
        {"month",           &MonthMustache::getMonth},
        {"file_name",       &MonthMustache::getFileName},
        {"show_categories", &MonthMustache::getShowCategories},
        {"show_epics",      &MonthMustache::getShowEpics},
        {"show_comments",   &MonthMustache::getShowComments},
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

  mstch::node MonthMustache::getShowCategories() noexcept
  {
    return this->showCategories;
  }

  mstch::node MonthMustache::getShowEpics() noexcept
  {
    return this->showEpics;
  }

  mstch::node MonthMustache::getShowComments() noexcept
  {
    return this->showComments;
  }
} // Wallet::Mustache Namespace


#include "debug.hpp"
#include "year_mustache.hpp"
#include "class/epic.hpp"

namespace Wallet::Mustache
{
  YearMustache::YearMustache(std::string _rel, mstch::array _entries, mstch::map _total,
                             std::string _year, Container::CategoryArray _categoryNames, Container::EpicMap _epics,
                             std::string _pngFileName) :
    BaseMustache{std::move(_rel), std::move(_entries), std::move(_total)},
    year(std::move(_year)), categoryNames(std::move(_categoryNames)), epics(std::move(_epics)), pngFileName(std::move(_pngFileName))
  {
    //DLog(" -> YearMustache::YearMustache('%s', '%s', %lu)\n",
    //  _rel.c_str(), this->year.c_str(), _categoryNames.size());

    this->register_methods(this, {
      {"year",           &YearMustache::getYear},
      {"category_count", &YearMustache::getCategoryCount},
      {"categories",     &YearMustache::getCategories},
      {"epic_count",    &YearMustache::getEpicCount},
      {"epics",          &YearMustache::getEpics},
      {"png_file_name",  &YearMustache::getPngFileName},
    });
  }

  mstch::node YearMustache::getYear() noexcept
  {
    //DLog(" -> YearMustache::getYear()\n");
    return this->year;
  }

  mstch::node YearMustache::getCategoryCount() noexcept
  {
    //DLog(" -> YearMustache::getCategoryCount() -> %lu\n", this->categoryNames.size());
    return std::to_string(this->categoryNames.size());
  }

  mstch::node YearMustache::getCategories() noexcept
  {
    //DLog(" -> YearMustache::getCategories() -> %lu\n", this->categoryNames.size());

    // Iterators
    const auto cnb = this->categoryNames.cbegin();
    const auto cne = this->categoryNames.cend();

    mstch::array names{};

    // Transform vector of names to map with 'name' property.
    std::transform(cnb, cne, std::back_inserter(names), [](std::string name) {
      //DLog(" -> transform: '%s'\n", name.c_str());
      return mstch::map{
        {"name", std::move(name)},
      };
    });

    return names;
  }

  mstch::node YearMustache::getEpicCount() noexcept
  {
    DLog(" -> YearMustache::getEpicCount() -> %lu\n", this->epics.size());
    return std::to_string(this->epics.size());
  }

  mstch::node YearMustache::getEpics() noexcept
  {
    DLog(" -> YearMustache::getEpics() -> %lu\n", this->epics.size());

    // Iterators
    // const auto _begin <= this->epics.cbegin(); // Epic Names Begin
    // const auto _end   = this->epics.cend();   // Epic Names End

    mstch::array _epics{};

    // Transform vector of epics to map.
    /*std::transform(_begin, _end, std::back_inserter(_epics), [](const Epic& epic) {
      DLog(" -> transform epics\n");
      // DLog(" -> transform: '%s'\n", epic.handle.c_str());

      return mstch::map{
        // {"handle", std::move(epic.handle)},
        {"handle", std::string{"test"}},
      };
    });*/
    

    return _epics;
  }

  mstch::node YearMustache::getPngFileName() noexcept
  {
    //DLog(" -> YearMustache::getPngFileName()\n");
    return this->pngFileName;
  }
} // Wallet::Mustache Namespace

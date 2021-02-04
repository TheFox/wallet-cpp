
#include "debug.hpp"
#include "year_mustache.hpp"
#include "class/epic.hpp"

namespace Wallet::Mustache
{
  YearMustache::YearMustache(std::string _rel, mstch::array _entries, mstch::map _total,
        std::string _year, Container::UnsortedCategories _categoryNames,
        Container::SortedEpicPtrs _epicPtrs, std::string _pngFileName) :
      BaseMustache{std::move(_rel), std::move(_entries), std::move(_total)},
      year(std::move(_year)), categoryNames(std::move(_categoryNames)), epicPtrs(_epicPtrs), pngFileName(
      std::move(_pngFileName))
  {
    //DLog("-> YearMustache::YearMustache('%s', '%s', %lu)\n",
    //  _rel.c_str(), this->year.c_str(), _categoryNames.size());

    this->register_methods(this, {
        {"year",           &YearMustache::getYear},
        {"category_count", &YearMustache::getCategoryCount},
        {"categories",     &YearMustache::getCategories},
        {"epic_count",     &YearMustache::getEpicCount},
        {"epics",          &YearMustache::getEpics},
        {"has_epics",      &YearMustache::getHasEpics},
        {"png_file_name",  &YearMustache::getPngFileName},
    });
  }

  mstch::node YearMustache::getYear() noexcept
  {
    //DLog("-> YearMustache::getYear()\n");
    return this->year;
  }

  mstch::node YearMustache::getCategoryCount() noexcept
  {
    //DLog("-> YearMustache::getCategoryCount() -> %lu\n", this->categoryNames.size());
    return std::to_string(this->categoryNames.size());
  }

  mstch::node YearMustache::getCategories() noexcept
  {
    //DLog("-> YearMustache::getCategories() -> %lu\n", this->categoryNames.size());

    // Iterators
    const auto _begin = this->categoryNames.cbegin();
    const auto _end = this->categoryNames.cend();

    mstch::array names{};

    // Transform vector of names to map with 'name' property.
    std::transform(_begin, _end, std::back_inserter(names), [](std::string name) {
      //DLog("-> transform: '%s'\n", name.c_str());
      return mstch::map{
          {"name", std::move(name)},
      };
    });

    return names;
  }

  mstch::node YearMustache::getEpicCount() noexcept
  {
    // DLog("-> YearMustache::getEpicCount() -> %lu\n", this->epics.size());

    return std::to_string(this->epicPtrs.size());
  }

  mstch::node YearMustache::getEpics() noexcept
  {
    // DLog("-> YearMustache::getEpics() -> %lu\n", this->epics.size());

    mstch::array _epics{};

    // Transform vector of epics to map.
    for (const auto& pair : this->epicPtrs) {
      // DLog("-> YearMustache::getEpics() -> pair: '%s'\n", pair.first.c_str());

      const auto& epicPtr = pair.second;

      std::string epicHandle{"default"};
      std::string epicTitle{"default"};
      std::string epicBgColor{"#ffffff"};

      if (epicPtr != nullptr) {
        epicHandle = epicPtr->handle;
        epicTitle = epicPtr->title;
        epicBgColor = epicPtr->bgColor;
      }

      mstch::map _emap{
          {"handle",   std::move(epicHandle)},
          {"title",    std::move(epicTitle)},
          {"bg_color", std::move(epicBgColor)},
      };
      _epics.push_back(_emap);
    }

    return _epics;
  }

  mstch::node YearMustache::getHasEpics() noexcept
  {
    //DLog("-> YearMustache::getHasEpics() -> %lu\n", this->epics.size());
    return this->epicPtrs.size() > 0;
  }

  mstch::node YearMustache::getPngFileName() noexcept
  {
    //DLog("-> YearMustache::getPngFileName()\n");
    return this->pngFileName;
  }
} // Wallet::Mustache Namespace

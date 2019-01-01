
#include "debug.hpp"
#include "year_mustache.hpp"

namespace Wallet::Mustache
{
  YearMustache::YearMustache(std::string _rel, mstch::array _entries, mstch::map _total,
                             std::string _year, Container::CategoryArray _categoryNames,
                             std::string _pngFileName) :
    BaseMustache{std::move(_rel), std::move(_entries), std::move(_total)},
    year(std::move(_year)), categoryNames(std::move(_categoryNames)), pngFileName(std::move(_pngFileName))
  {
    //DLog(" -> YearMustache::YearMustache('%s', '%s', %lu)\n",
    //  _rel.c_str(), this->year.c_str(), _categoryNames.size());

    this->register_methods(this, {
      {"year",           &YearMustache::getYear},
      {"category_count", &YearMustache::getCategoryCount},
      {"categories",     &YearMustache::getCategories},
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

  mstch::node YearMustache::getPngFileName() noexcept
  {
    //DLog(" -> YearMustache::getPngFileName()\n");
    return this->pngFileName;
  }
} // Wallet::Mustache Namespace

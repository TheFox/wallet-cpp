
#include "debug.hpp"
#include "config.hpp"
#include "index_mustache.hpp"

namespace Wallet::Mustache
{
  IndexMustache::IndexMustache(mstch::array _entries, mstch::map _total, mstch::array _categories, mstch::array _epics) :
    BaseMustache{std::move(_entries), std::move(_total)},
    categories(std::move(_categories)), epics(std::move(_epics))
  {
    //DLog(" -> IndexMustache::IndexMustache() -> %lu entries, %lu totals\n", this->entries.size(), this->total.size());

    this->register_methods(this, {
      {"category_count",  &IndexMustache::getCategoryCount},
      {"categories",      &IndexMustache::getCategories},
      {"has_categories",  &IndexMustache::getHasCategories},

      {"epic_count",      &IndexMustache::getEpicCount},
      {"epics",           &IndexMustache::getEpics},
      {"has_epics",       &IndexMustache::getHasEpics},
    });
  }

  mstch::node IndexMustache::getCategoryCount() noexcept
  {
    //DLog(" -> IndexMustache::getCategoryCount() -> %lu\n", this->categories.size());

    return std::to_string(this->categories.size());
  }

  mstch::node IndexMustache::getCategories() noexcept
  {
    //DLog(" -> IndexMustache::getCategories() -> %lu\n", this->categories.size());

    return this->categories;
  }

  mstch::node IndexMustache::getHasCategories() noexcept
  {
    //DLog(" -> IndexMustache::getHasCategories() -> %lu\n", this->categories.size());

    return this->categories.size() > 0;
  }

  mstch::node IndexMustache::getEpicCount() noexcept
  {
    //DLog(" -> IndexMustache::getEpicCount() -> %lu\n", this->epics.size());

    return std::to_string(this->epics.size());
  }

  mstch::node IndexMustache::getEpics() noexcept
  {
    //DLog(" -> IndexMustache::getEpics() -> %lu\n", this->epics.size());

    return this->epics;
  }

  mstch::node IndexMustache::getHasEpics() noexcept
  {
    //DLog(" -> IndexMustache::getHasEpics() -> %lu\n", this->epics.size());
    
    return this->epics.size() > 0;
  }
} // Wallet::Mustache Namespace

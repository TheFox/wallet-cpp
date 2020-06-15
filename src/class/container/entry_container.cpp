
#include "debug.hpp"
#include "entry_container.hpp"

namespace Wallet::Container
{
  void CategoryContainer::set(std::string _category) noexcept
  {
    //DLog("-> CategoryContainer::set('%s')\n", _category.c_str());

    if (_category == "default") {
      return;
    }

    this->category = std::move(_category);
    this->isDefaultCategory = false;
  }

  BaseCategoryContainer::BaseCategoryContainer()
  {
    this->categories["default"];
  }

  bool CategoryComparator::operator()(const std::string& c1, const std::string& c2) const
  {
    //DLog("-> CategoryComparator::operator(%s, %s)\n", c1.c_str(), c2.c_str());

    if (c1 == c2) {
      return false;
    }

    // Make 'default' always first.
    if (c1 == "default") {
      return true;
    }
    if (c2 == "default") {
      return false;
    }

    return c1 < c2;
  }
} // Wallet::Container Namespace


#include "debug.hpp"
#include "entry_container.hpp"

namespace Wallet::Container
{
  BaseCategoryContainer::BaseCategoryContainer()
  {
    this->categories["default"];
  }

  bool CategoryComparator::operator()(const std::string& c1, const std::string& c2) const
  {
    //DLog(" -> CategoryComparator::operator(%s, %s)\n", c1.c_str(), c2.c_str());

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


#ifdef __has_include
#  if __has_include(<termcolor/termcolor.hpp>)
#    include <termcolor/termcolor.hpp>
#  endif
#endif // __has_include

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

  // Sort Categories by name.
  bool CategoryComparator::operator()(const std::string& item1, const std::string& item2) const
  {
    // DLog("-> CategoryComparator::operator()(%s, %s) -> %d\n", item1.c_str(), item2.c_str(), item1 < item2);

#include "comparator.hpp"

  }
} // Wallet::Container Namespace

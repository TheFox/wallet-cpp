
#include "debug.hpp"
#include "epic_container.hpp"

namespace Wallet::Container
{
  BaseEpicContainer::BaseEpicContainer()
  {
    //DLog(" -> BaseEpicContainer::BaseEpicContainer()\n");

    // Default Epic
    this->epics["default"];
  }

  bool EpicComparator::operator()(const std::string& epic1, const std::string& epic2) const
  {
    DLog(" -> EpicComparator::operator(%s, %s)\n", epic1.c_str(), epic2.c_str());

    if (epic1 == epic2) {
      return false;
    }

    // Make 'default' always first.
    if (epic1 == "default") {
      return true;
    }
    if (epic2 == "default") {
      return false;
    }

    return epic1 < epic2;
  }
} // Wallet::Container Namespace

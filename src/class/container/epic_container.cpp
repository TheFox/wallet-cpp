
#ifdef __has_include
#  if __has_include(<termcolor/termcolor.hpp>)
#    include <termcolor/termcolor.hpp>
#  endif
#endif // __has_include

#include "debug.hpp"
#include "epic_container.hpp"

namespace Wallet::Container
{
  void EpicContainer::set(EpicPtr _epicPtr) noexcept
  {
    // DLog("-> EpicContainer::set('%s')\n", _epicPtr->handle.c_str());

    if (this->epicPtr) {
      // std::cerr << "    " << termcolor::on_red << termcolor::white << "-> skip epic set " << _epicPtr->handle << termcolor::reset << std::endl;
      return;
    }

    if (_epicPtr->handle != "default") {
      this->isDefaultEpic = false;

      // std::cerr << "    " << termcolor::on_green << termcolor::white << "-> epic set " << _epicPtr->handle << termcolor::reset << std::endl;
    }
    this->epicPtr = std::move(_epicPtr);
  }

  BaseEpicContainer::BaseEpicContainer()
  {
    //DLog("-> BaseEpicContainer::BaseEpicContainer()\n");

    // Default Epic
    this->epics["default"];
  }

  // Sort Epics by Handle.
  bool EpicComparator::operator()(const std::string& item1, const std::string& item2) const
  {
    // DLog("-> EpicComparator::operator()(%s, %s)\n", item1.c_str(), item2.c_str());

#include "comparator.hpp"

  }
} // Wallet::Container Namespace

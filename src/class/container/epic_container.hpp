
#ifndef WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

#include <string>
//#include <utility> // pair
#include <map>
//#include <cstdint> // uint8_t
#include <functional> // function

//#include "class/entry.hpp"
#include "class/accountable.hpp"

namespace Wallet::Container
{
  // Types
  //using EpicArray = std::vector<Epic>;

  struct EpicContainer final : public Accountable
  {
  };

  /**
   * Compare Epics by name.
   */
  class EpicComparator
  {
  public:
    bool operator()(const std::string&, const std::string&) const;
  };

  using EpicArray = std::vector<std::string>;
  using EpicMap = std::map<std::string, EpicContainer, EpicComparator>;
  struct BaseEpicContainer
  {
    BaseEpicContainer();

    // Properties
    EpicMap epics{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

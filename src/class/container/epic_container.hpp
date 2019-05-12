
#ifndef WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

#include <string>
#include <map>
#include <functional> // function

#include "class/epic.hpp"
#include "class/trait/accountable.hpp"

namespace Wallet::Container
{
  // Types
  //using EpicArray = std::vector<Epic>;

  struct EpicContainer final : public Wallet::Trait::Accountable
  {
  };

  /**
   * Compare Epics by name.
   */
  class EpicComparator
  {
  public:
    bool operator()(const std::string&, const std::string&) const;
    // bool operator()(const Epic&, const Epic&) const;
  };

  using EpicArray = std::vector<Epic>;
  using EpicMap = std::map<std::string, EpicContainer, EpicComparator>;
  struct BaseEpicContainer
  {
    BaseEpicContainer();

    // Properties
    EpicMap epics{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_


#ifndef WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

#include <string>
#include <map>

#include "class/epic.hpp"
#include "class/trait/accountable.hpp"

namespace Wallet::Container
{
  struct EpicContainer final : public Wallet::Trait::Accountable
  {
    // Properties
    Epic epic{};
    bool isDefaultEpic{true};
  };

  /**
   * Compare Epics by name.
   */
  class EpicComparator
  {
  public:
    bool operator()(const std::string&, const std::string&) const;
  };

  using EpicArray = std::vector<Epic>;
  using EpicMap = std::map<std::string, EpicContainer, EpicComparator>;
  using Epics = std::map<std::string, Epic>;
  struct BaseEpicContainer
  {
    BaseEpicContainer();

    // Properties
    EpicMap epics{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

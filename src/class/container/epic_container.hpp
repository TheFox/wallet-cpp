
#ifndef WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_
#define WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

#include <string>
#include <map>
#include <memory> // shared_ptr

#include "class/epic.hpp"
#include "class/trait/accountable.hpp"

namespace Wallet::Container
{
  // Types
  using EpicArray = std::vector<Epic>;
  using UnsortedEpics = std::map<std::string, Epic>;
  using EpicPtr = std::shared_ptr<Epic>;

  struct EpicContainer final : public Wallet::Trait::Accountable
  {
    // Properties
    Epic epic{};
    EpicPtr epicPtr{};
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

  using SortedEpics = std::map<std::string, EpicContainer, EpicComparator>;
  struct BaseEpicContainer
  {
    BaseEpicContainer();

    // Properties
    SortedEpics epics{};
  };
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

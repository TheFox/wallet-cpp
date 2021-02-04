
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
  using EpicPtr = std::shared_ptr<Epic>;
  using EpicPtrArray = std::vector<EpicPtr>;

  struct EpicContainer final : public Wallet::Trait::Accountable
  {
    EpicPtr epicPtr{};
    bool isDefaultEpic{true};
    void set(EpicPtr) noexcept;
  };

  /**
   * Sort Epics by Handle.
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

  using SortedEpicPtrs = std::map<std::string, EpicPtr, EpicComparator>;
} // Wallet::Container Namespace

#endif // WALLETCPP_CONTAINER_EPIC_CONTAINER_HPP_

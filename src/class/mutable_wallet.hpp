
#ifndef WALLETCPP_MUTABLE_WALLET_HPP_
#define WALLETCPP_MUTABLE_WALLET_HPP_

#include <string>
#include <vector>
#include <cstdint> // uint8_t

#include "fs.hpp"
#include "trait/logable.hpp"
#include "components.hpp"
#include "entry.hpp"
#include "epic.hpp"
#include "container/entry_container.hpp"
#include "container/epic_container.hpp"

#define WALLET_MONTH_FILE_VERSION 2

namespace Wallet
{
  class MutableWallet final : public Trait::Logable
  {
  public:
    // Constructor
    explicit MutableWallet(std::string) noexcept;

    // Destructor
    ~MutableWallet() noexcept;

    // Public Functions
    void init() noexcept;
    bool addUniqueEntry(const Entry&);
    bool addEntry(const Entry&);
    void htmlOutput(const std::string&, const std::string& = "", const std::string& = "") const;
    void addEpic(const Epic&) noexcept;
    void removeEpic(const std::string&) noexcept;
    void updateEpic(const Epic&) noexcept;
    Epic getEpicByHandle1(std::string) const;
    Container::EpicPtr getEpicByHandle2(std::string) const;
    bool epicExists(const std::string&) noexcept;
    bool epicExists(const Epic&) noexcept;
    Container::EntryContainer getEntries(const Components::Date&,
                                         const std::string& = "",
                                         const std::string& = "") const;

  private:
    // Variables
    const fs::path path{};
    const fs::path dataPath{};
    const fs::path indexPath{};
    const fs::path epicsPath{};
    const fs::path tmpPath{};
    const fs::path lockPath{};

    const std::uint8_t version{1};
    bool hasSetup{};
    bool isLocked{};
    bool isIndexLoaded{};
    bool isIndexModified{};
    YAML::Node index{};
    bool areEpicsModified{};
    mutable bool areEpicsLoaded{};
    mutable YAML::Node epics{}; // TODO Change this to Assoc Array instead of YAML::Node

    // Functions
    void setup();
    void setupDirectories() noexcept;
    void createLock();
    void removeLock() noexcept;
    void loadIndex() noexcept;
    void saveIndex() noexcept;
    bool entryExists(const Entry&) noexcept;
    void loadEpics() const noexcept;
    void loadEpics() noexcept;
    void saveEpics() noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_MUTABLE_WALLET_HPP_

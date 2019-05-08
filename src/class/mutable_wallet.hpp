
#ifndef WALLETCPP_MUTABLE_WALLET_HPP_
#define WALLETCPP_MUTABLE_WALLET_HPP_

#include <string>
#include <vector>
#include <cstdint> // uint8_t

#include "fs.hpp"
#include "logable.hpp"
#include "components.hpp"
#include "entry.hpp"
#include "container/entry_container.hpp"

#define WALLET_MONTH_FILE_VERSION 2

namespace Wallet
{
  class MutableWallet final : public Logable
  {
  public:
    // Constructor
    explicit MutableWallet(std::string) noexcept;

    // Destructor
    ~MutableWallet() noexcept;

    // Public Commands
    void init() noexcept;
    bool add(const Entry&, bool);
    void htmlOutput(const std::string&) const;

    // Public Functions
    Container::EntryContainer getEntries(const Components::Date&,
      const std::string& = "",
      const std::string& = "") const;

  private:
    // Variables
    const fs::path path{};
    const fs::path dataPath{};
    const fs::path indexPath{};
    const fs::path tmpPath{};
    const fs::path lockPath{};

    const std::uint8_t version{1};
    bool hasSetup{};
    bool isLocked{};
    bool isIndexLoaded{};
    bool isIndexModified{};
    YAML::Node index{};

    // Functions
    void setup();
    void setupDirectories() noexcept;
    void createLock();
    void removeLock() noexcept;
    void loadIndex() noexcept;
    void saveIndex() noexcept;
    bool entryExists(const Entry&) noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_MUTABLE_WALLET_HPP_


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
  class MutableWallet : public Logable
  {
  public:
    // Constructor
    explicit MutableWallet(std::string) noexcept;

    // Destructor
    ~MutableWallet() noexcept;

    // Functions
    virtual void setup();
    void setup(bool);
    virtual bool add(const Entry&, bool);
    Container::EntryContainer getEntries(const Components::Date&) const;
    void htmlOutput(const std::string&) const;

  protected:
    // Variables
    const fs::path path{};
    fs::path dataPath{};
    fs::path indexPath{};
    fs::path tmpPath{};
    fs::path lockPath{};

    // Functions
    void setupVariables() noexcept;
    void setupDirectories(bool) noexcept;

  private:
    // Variables
    std::uint8_t version{1};
    bool isLocked{};
    bool isIndexLoaded{};
    bool isIndexModified{};
    YAML::Node index{};

    // Functions
    void createLock();
    void removeLock() noexcept;
    void loadIndex() noexcept;
    void saveIndex() noexcept;
    bool entryExists(const Entry&) noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_MUTABLE_WALLET_HPP_

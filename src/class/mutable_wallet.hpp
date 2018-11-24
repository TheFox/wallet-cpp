
#ifndef WALLETCPP_MUTABLE_WALLET_HPP_
#define WALLETCPP_MUTABLE_WALLET_HPP_

#include <string>
#include <vector>

#ifdef __has_include
#  if __has_include(<filesystem>)
#    include <filesystem>
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#  else
#    error "Missing <filesystem>"
#  endif
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "entry.hpp"

#define WALLET_MONTH_FILE_VERSION 2

namespace Wallet
{
  class MutableWallet
  {
  public:
    // Types
    using EntryMap = std::map<std::string, std::vector<Entry>>;

    // Constructor
    explicit MutableWallet(std::string) noexcept;

    // Destructor
    ~MutableWallet() noexcept(noexcept(this->saveIndex()) && noexcept(this->removeLock()));

    // Functions
    virtual void setup();
    void setup(bool);
    virtual bool add(Entry, bool);
    EntryMap getEntries() const;
    //void getEntries(u_int) const; // Year
    //void getEntries(u_int, u_int) const; // Year, Month
    //void getEntries(u_int, u_int, u_int) const; // Year, Month, Day

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

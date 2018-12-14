
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
#  if __has_include(<optional>)
#    include <optional>
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
#  elif __has_include(<boost/optional.hpp>)
#    include <boost/optional.hpp>
#  else
#    error "Missing <optional>"
#  endif
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#  if __has_include(<CTML/CTML.h>)
#    include <CTML/CTML.h>
#  else
#    error "Missing <CTML/CTML.h>"
#  endif
#endif // __has_include

#include "entry.hpp"
#include "entry_container.hpp"
#include "../components.hpp"

#define WALLET_MONTH_FILE_VERSION 2

namespace Wallet
{
  class MutableWallet
  {
  public:
    // Constructor
    explicit MutableWallet(std::string) noexcept;

    // Destructor
    ~MutableWallet() noexcept(noexcept(this->saveIndex()) && noexcept(this->removeLock()));

    // Functions
    virtual void setup();
    void setup(bool);
    virtual bool add(Entry, bool);
    Container::EntryContainer getEntries(Components::Date) const;
    // void htmlOutput(const std::optional<std::string>&) const noexcept;
    void htmlOutput(const std::string&) const noexcept;
  private:
    void htmlOutputYear(const Container::YearEntryContainer&, const fs::path&) const noexcept;
    void htmlOutputMonth(const Container::MonthEntryContainer&) const noexcept;
    void htmlOutputDay(const Container::DayEntryContainer&) const noexcept;
    CTML::Node getHtmlSignatur() const noexcept;

  protected:
    // Variables
    const fs::path path{};
    fs::path dataPath{};
    mutable fs::path htmlPath{};
    fs::path indexPath{};
    fs::path tmpPath{};
    fs::path lockPath{};

    // Functions
    void setupVariables() noexcept;
    void setupDirectories(bool) noexcept;

  private:
    // Variables
    u_int8_t version{1};
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

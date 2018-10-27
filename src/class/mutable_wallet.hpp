
#ifndef WALLETCPP_MUTABLE_WALLET_HPP_
#define WALLETCPP_MUTABLE_WALLET_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<filesystem>)
#    include <filesystem>
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#  else
#     error "Missing <filesystem>"
#  endif
#endif // __has_include

namespace Wallet
{
  class Entry;

  class MutableWallet
  {
  public:
    // Constructor
    explicit MutableWallet(std::string);

    // Functions
    virtual void setup() noexcept;
    void setup(bool) noexcept;
    virtual bool add(Entry, bool);

  protected:
    // Variables
    const fs::path path;
    fs::path dataPath;
    fs::path indexPath;
    fs::path tmpPath;

    // Functions
    void setupVariables() noexcept;
    void setupDirectories(bool) noexcept;

  private:
    // Variables
    bool isIndexLoaded;
    bool isIndexModified;

    // Functions
    void loadIndex() noexcept;
    void saveIndex() noexcept;
    bool entryExist(const Entry&) noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_MUTABLE_WALLET_HPP_

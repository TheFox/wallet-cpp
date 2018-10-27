
#ifndef WALLETCPP_MUTABLE_WALLET_HPP_
#define WALLETCPP_MUTABLE_WALLET_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<optional>)
#    include <optional>
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
#  elif __has_include(<boost/optional.hpp>)
#    include <boost/optional.hpp>
#  else
#     error "Missing <optional>"
#  endif
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

#define WALLET_DEFAULT_PATH ".wallet"

namespace Wallet
{
  class Entry;

  class MutableWallet
  {
  public:
    MutableWallet();
    explicit MutableWallet(std::string);
    explicit MutableWallet(std::optional<std::string>);
    virtual bool add(Entry);
    virtual bool add(Entry, bool);

  protected:
    // Variables
    const fs::path path;
    fs::path dataPath;
    fs::path tmpPath;

    // Functions
    virtual void setup() noexcept;
    void setupVariables() noexcept;
    void setupDirectories() noexcept;
  };
} // Wallet Namespace

#endif // WALLETCPP_MUTABLE_WALLET_HPP_

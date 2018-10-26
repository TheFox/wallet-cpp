
#ifndef WALLET_WALLET_HPP_
#define WALLET_WALLET_HPP_

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
#endif // __has_include

#define WALLET_DEFAULT_PATH ".wallet"

namespace Wallet
{
  class Entry;

  class Wallet final
  {
  public:
    Wallet();
    explicit Wallet(std::string);
    explicit Wallet(std::optional<std::string>);
    bool add(Entry) noexcept;
    bool add(Entry, bool) noexcept;

  private:
    const std::string path;
  };
} // Wallet Namespace

#endif // WALLET_WALLET_HPP_

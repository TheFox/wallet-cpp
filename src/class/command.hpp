
#ifndef WALLETCPP_COMMAND_HPP_
#define WALLETCPP_COMMAND_HPP_

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

namespace Wallet
{
  struct CommandOptions
  {
    std::optional<std::string> walletPath;

    // Status
    bool isInteractively;
  };

  class Command
  {
  public:
    Command();
    virtual ~Command() = 0;
    virtual int execute() = 0;
    void setOptions(CommandOptions) noexcept;

  protected:
    CommandOptions commandOptions;
  };
} // Wallet Namespace

#endif // WALLETCPP_COMMAND_HPP_

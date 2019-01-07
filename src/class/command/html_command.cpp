
#include <string>
#include <cstdlib> // system

#include "debug.hpp"
#include "config.hpp"
#include "html_command.hpp"
#include "class/immutable_wallet.hpp"

namespace Wallet
{
  int HtmlCommand::execute()
  {
#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> check 'gnuplot' command\n");
    const auto gpls = std::system("gnuplot --version &> /dev/null < /dev/null");
    DLog(" -> check 'gnuplot' command: %d\n", gpls);
    if (gpls != 0) {
      throw std::string{"gnuplot not installed or not in PATH."};
    }
#endif

    ImmutableWallet wallet{this->options.walletPath};
    wallet.logLevel = this->options.verbose;
    wallet.setup();

    // TODO: date
    // TODO: category
    wallet.htmlOutput(this->options.path);

    return Command::execute();
  }
} // Wallet Namespace

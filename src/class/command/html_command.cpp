
#include <string>

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
    const auto gpls = system("gnuplot --help &> /dev/null < /dev/null");
    DLog(" -> check 'gnuplot' command: %d\n", gpls);
    if (gpls != 0) {
      throw std::string{"gnuplot not installed or not in PATH."};
    }
#endif

    ImmutableWallet wallet{this->options.walletPath};
    wallet.setup();

    wallet.htmlOutput(this->options.path);

    return Command::execute();
  }
} // Wallet Namespace

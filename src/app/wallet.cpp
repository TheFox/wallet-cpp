
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>

#ifdef __has_include
#  if __has_include(<boost/program_options.hpp>)
#    include <boost/program_options.hpp>
#  else
#     error "Missing <program_options>"
#  endif
#endif // __has_include

#include <termcolor/termcolor.hpp>

#include "../config.hpp"
#include "../class/command_factory.hpp"
#include "../class/command.hpp"

namespace bpo = boost::program_options;

//void to_cout(const std::vector<std::string>& v)
//{
//  std::copy(begin(v), end(v),
//    std::ostream_iterator<std::string>{std::cout, "\n"});
//}

int main(int argc, char* const argv[])
{
  using std::string;
  using std::cout;
  using std::cerr;
  using std::endl;
  using bpo::options_description;
  using bpo::value;
  using Wallet::CommandFactory;
  using Wallet::CommandOptions;

#ifdef DEBUG
  puts("--- DEBUG ---");
  printf("__clang_version__ %s\n", __clang_version__);
  puts("");
#endif

  // Commands
  bpo::positional_options_description commandPos;
  commandPos.add("command", 1);

  // Generic options
  options_description commandOpts("Commands");
  commandOpts.add_options()
               ("command", value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing(),
                 "Commands");

  // Generic options
  options_description genericOpts("Generic options");
  genericOpts.add_options()
               ("help,h", "This message")
               ("wallet,w", value<string>()->value_name("path"), "Path to the wallet directory.");

  // Common options
  options_description commonOpts("Common options");
  commonOpts.add_options()
              ("interactive,i", "Use some commands interactively.");

  options_description opts;
  opts.add(commandOpts).add(genericOpts).add(commonOpts);

  auto parsedOptions = bpo::command_line_parser(argc, argv)
    .options(opts)
    .positional(commandPos)
    .allow_unregistered()
    .run();

  bpo::variables_map vm{};
  bpo::store(parsedOptions, vm);
  bpo::notify(vm);

  string commandName{};
  if (vm.count("command")) {
    auto commands = vm["command"].as<std::vector<std::string>>();
    if (!commands.empty()) {
      commandName = commands.front();
    }
  }

  if (vm.count("help") || commandName.empty()) {
    cout << PROJECT_NAME
         << PROJECT_VERSION_MAJOR << '.' << PROJECT_VERSION_MINOR << '.' << PROJECT_VERSION_PATCH
         << PROJECT_VERSION_APPENDIX << endl;
    cout << PROJECT_COPYRIGHT << endl << endl;

    cout << "Usage: " << argv[0] << " <command> [options]" << endl << endl;
    cout << "Commands:" << endl;
    cout << "  add    Add a new entry" << endl;
    cout << endl;
    cout << genericOpts << endl;
    cout << commonOpts << endl;

    return 3;
  }

  CommandOptions cmdOpts = {};

  if (vm.count("wallet")) {
    cmdOpts.walletPath = vm["wallet"].as<std::string>();
  }
  if (vm.count("interactive")) {
    cmdOpts.isInteractively = true;
  }

  CommandFactory::setup();
  CommandFactory factory;

  try {
    auto command = factory.getCommand(commandName);
    command->setOptions(cmdOpts);
    return command->execute();
  }
  catch (const std::string& e) {
    cerr << termcolor::on_red << termcolor::white << "ERROR: " << e << termcolor::reset << endl;
    return 1;
  }
}


#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unistd.h>

#ifdef __has_include
#  if __has_include(<boost/program_options.hpp>)
#    include <boost/program_options.hpp>
namespace bpo = boost::program_options;
#  else
#    error "Missing <program_options>"
#  endif
#  if __has_include(<termcolor/termcolor.hpp>)
#    include <termcolor/termcolor.hpp>
#  endif
#endif // __has_include

#include "debug.hpp"
#include "config.hpp"
#include "components.hpp"
#include "class/command/command_options.hpp"
#include "class/command/command_factory.hpp"
#include "class/command/command.hpp"
#include "class/command/version_command.hpp"

int main(int argc, char* const argv[])
{
  DLog("--- DEBUG ---\n");

  // Commands
  bpo::positional_options_description commandPos{};
  commandPos.add("command", 1);

  // Generic options
  bpo::options_description commandOpts{"Commands"};
  commandOpts.add_options()
               ("command", bpo::value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing(),
                 "Commands");

  // Generic options
  bpo::options_description genericOpts{"Generic options"};
  genericOpts.add_options()
               ("help,h", "This message")
               ("version", "Prints version.")
               ("verbose,v", "Verbose output.")
               ("wallet,w", bpo::value<std::string>()->value_name("path"), "Path to the wallet directory.");

  // Common options
  bpo::options_description commonOpts{"Common options"};
  commonOpts.add_options()
              ("title,t", bpo::value<std::string>()->value_name("string"), "Set a Title for Entry or Epic.")
              ("date,d", bpo::value<std::string>()->value_name("string"), "Set or filter by Date. (Format: YYYY-MM-DD)")
              ("category,c", bpo::value<std::string>()->value_name("string"), "Set or filter by Category.")
              ("epic,x", bpo::value<std::string>()->value_name("string"), "Set or filter by Epic handle.");

  // Add Command options
  bpo::options_description addCmdOpts{"Add Command options"};
  addCmdOpts.add_options()
              ("id", bpo::value<std::string>()->value_name("string"), "Set a unique ID.")
              ("message,m", bpo::value<std::string>()->value_name("string"), "Alias for --title.")
              ("revenue,r", bpo::value<std::string>()->value_name("number"), "Set a  Revenue.")
              ("expense,e", bpo::value<std::string>()->value_name("number"), "Set an Expense.")

              ("comment,o", bpo::value<std::string>()->value_name("string"), "Set a Comment.")

              ("interactive,i", "Add entry interactively.")
              ("force,f", "Force add command. Even if ID is set and already exists.")
              ("no-force", "Do not force add command.");

  // HTML Command options
  bpo::options_description htmlCmdOpts{"HTML Command options"};
  htmlCmdOpts.add_options()
               ("path,p", bpo::value<std::string>()->value_name("string"),
                 "Output directory path. Default: <wallet>/html");

  // Epic Command options
  bpo::options_description epicCmdOpts{"Epic Command options"};
  epicCmdOpts.add_options()
              ("handle", bpo::value<std::string>()->value_name("string"),
                "Handle (For example 'myepic')")
              ("bgcolor", bpo::value<std::string>()->value_name("string"), "Background Color (HTML)")
              ("remove,R", "Remove Epic by handle.");

  bpo::options_description opts{};
  opts
    .add(commandOpts)
    .add(genericOpts)
    .add(commonOpts)
    .add(addCmdOpts)
    .add(htmlCmdOpts)
    .add(epicCmdOpts)
  ;

  auto parsedOptions = bpo::command_line_parser(argc, argv)
    .options(opts)
    .positional(commandPos)
    .allow_unregistered()
    .run();

  bpo::variables_map vm{};
  bpo::store(parsedOptions, vm);
  bpo::notify(vm);

  std::string commandName{};
  if (vm.count("command")) {
    auto commands = vm["command"].as<std::vector<std::string>>();
    if (!commands.empty()) {
      commandName = commands.front();
    }
  }

  // Version
  if (vm.count("version")) {
    Wallet::VersionCommand versionCommand{};
    return versionCommand.execute();
  }

  // Help
  if (vm.count("help") || commandName.empty()) {
    std::cout << PROJECT_NAME << ' ' << PROJECT_VERSION_FULL << " (" << PROJECT_VERSION_HASH << ')' << std::endl;
    std::cout << "Built at: " << __DATE__ << ' ' << __TIME__ << std::endl;
    std::cout << PROJECT_COPYRIGHT << std::endl;
    std::cout << PROJECT_HOMEPAGE_URL << std::endl << std::endl;

    std::cout << "Usage: " << argv[0] << " <command> [options]" << std::endl << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  init      Initialize a new wallet" << std::endl;
    std::cout << "  add       Add a new entry" << std::endl;
    std::cout << "  list      List entries" << std::endl;
    std::cout << "  html      Generate HTML output" << std::endl;
    std::cout << "  epic      Manage epics" << std::endl;
    std::cout << std::endl;

    std::cout << genericOpts << std::endl;
    std::cout << commonOpts << std::endl;
    std::cout << addCmdOpts << std::endl;
    std::cout << htmlCmdOpts << std::endl;
    std::cout << epicCmdOpts << std::endl;

    std::cout << std::endl;
    std::cout << "Build settings:" << std::endl;

#ifdef __linux__
    std::cout << "  Built for Linux (__linux__)" << std::endl;
#endif
#ifdef __APPLE__
    std::cout << "  Built for Apple (__APPLE__)" << std::endl;
#endif
#ifdef __GNUC__
    std::cout << "  Built with: GCC " << __VERSION__ << std::endl;
#ifdef __llvm__
    std::cout << "              LLVM " << __clang_version__ << std::endl;
    std::cout << "              LLVM " << __clang_major__ << '.' << __clang_minor__ << '.' << __clang_patchlevel__
              << std::endl;
#endif
#else
    std::cout << "  Unknown build info. (Not implemented.) " << std::endl;
#endif

    std::cout << "  CMAKE_INSTALL_PREFIX: " << CMAKE_INSTALL_PREFIX << std::endl;
    std::cout << "  PROJECT_SHARE_PATH: " << PROJECT_SHARE_PATH << std::endl;
    std::cout << "  PROJECT_SHARE_PREFIX: " << PROJECT_SHARE_PREFIX << std::endl;
    std::cout << "  PROJECT_RESOURCES_PREFIX: " << PROJECT_RESOURCES_PREFIX << std::endl;

#ifdef WALLETCPP_GNUPLOT_SUPPORT
    std::cout << "  WALLETCPP_GNUPLOT_SUPPORT: YES" << std::endl;
#else
    std::cout << "  WALLETCPP_GNUPLOT_SUPPORT: NO" << std::endl;
#endif // WALLETCPP_GNUPLOT_SUPPORT

    std::cout << "  WALLETCPP_INDEX_VIEW_PATH: " << WALLETCPP_INDEX_VIEW_PATH << std::endl;
    std::cout << "  WALLETCPP_YEAR_VIEW_PATH: " << WALLETCPP_YEAR_VIEW_PATH << std::endl;
    std::cout << "  WALLETCPP_MONTH_VIEW_PATH: " << WALLETCPP_MONTH_VIEW_PATH << std::endl;
    std::cout << "  WALLETCPP_TOTAL_GNUPLOT_PATH: " << WALLETCPP_TOTAL_GNUPLOT_PATH << std::endl;
    std::cout << "  WALLETCPP_YEAR_GNUPLOT_PATH: " << WALLETCPP_YEAR_GNUPLOT_PATH << std::endl;

    return 3;
  }

  // Command Options
  Wallet::CommandOptions cmdOpts = {};

  if (vm.count("verbose")) {
    cmdOpts.verbose = 1;
  }
  if (vm.count("wallet")) {
    cmdOpts.walletPath = vm["wallet"].as<std::string>();
  }
  if (vm.count("id")) {
    cmdOpts.id = vm["id"].as<std::string>();
  }
  if (vm.count("title")) {
    cmdOpts.title = vm["title"].as<std::string>();
  }
  if (vm.count("message")) {
    cmdOpts.title = vm["message"].as<std::string>();
  }
  if (vm.count("date")) {
    cmdOpts.date = vm["date"].as<std::string>();
  }
  if (vm.count("revenue")) {
    const auto _tmpStr = vm["revenue"].as<std::string>();

    cmdOpts.revenue = Wallet::Components::stof(_tmpStr);
  }
  if (vm.count("expense")) {
    const auto _tmpStr = vm["expense"].as<std::string>();

    cmdOpts.expense = Wallet::Components::stof(_tmpStr);
  }
  if (vm.count("category")) {
    cmdOpts.category = vm["category"].as<std::string>();
  }
  if (vm.count("epic")) {
    cmdOpts.epic = vm["epic"].as<std::string>();
  }
  if (vm.count("comment")) {
    cmdOpts.comment = vm["comment"].as<std::string>();
  }
  if (vm.count("handle")) {
    cmdOpts.handle = vm["handle"].as<std::string>();
  }
  if (vm.count("bgcolor")) {
    cmdOpts.bgColor = vm["bgcolor"].as<std::string>();
  }
  if (vm.count("interactive")) {
    cmdOpts.isInteractively = true;
  }
  if (vm.count("force")) {
    cmdOpts.isForced = true;
  }
  if (vm.count("no-force")) {
    cmdOpts.isForced = false;
  }
  if (vm.count("remove")) {
    cmdOpts.isRemove = true;
  }
  if (vm.count("path")) {
    cmdOpts.path = vm["path"].as<std::string>();
  }

  // Command Factory
  Wallet::CommandFactory::setup();
  Wallet::CommandFactory factory{};

  try {
    auto command = factory.makeCommand(commandName);
    command->options = cmdOpts;
    return command->execute();
  }
  catch (const std::string& e) {
#ifdef TERMCOLOR_HPP_
    std::cerr << termcolor::on_red << termcolor::white << "ERROR: " << e << termcolor::reset << std::endl;
#else
    std::cerr << "ERROR: " << e << std::endl;
#endif
    return EXIT_FAILURE;
  }
}

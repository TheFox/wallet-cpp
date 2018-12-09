
#include <cstdio>
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

#include "config.hpp"
#include "../class/command/command_options.hpp"
#include "../class/command/command_factory.hpp"
#include "../class/command/command.hpp"
#include "../components.hpp"
#include "../debug.hpp"

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

  DLog("--- DEBUG ---\n\n");

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
              ("date,d", value<string>()->value_name("string"), "Set or filter by Date. (Format: YYYY-MM-DD)")
              ("category,c", value<string>()->value_name("string"), "Set or filter by Category.");

  // Add Command options
  options_description addCmdOpts("Add Command options");
  addCmdOpts.add_options()
              ("id", value<string>()->value_name("string"), "Set a unique ID.")
              ("title,t", value<string>()->value_name("string"), "Set a Title.")
              ("message,m", value<string>()->value_name("string"), "Alias for --title.")
              ("revenue,r", value<string>()->value_name("number"), "Set a  Revenue.")
              ("expense,e", value<string>()->value_name("number"), "Set an Expense.")

              ("comment,o", value<string>()->value_name("string"), "Set a Comment.")
              ("interactive,i", "Use some commands interactively.")
              ("force,f", "Force add command. Even if ID is set and already exists.")
              ("no-force", "Do not force add command.");

  // HTML Command options
  options_description htmlCmdOpts("HTML Command options");
  htmlCmdOpts.add_options()
               ("path,p", value<string>()->value_name("string"), "Output path. Default: <wallet>/html");

  options_description opts;
  opts
    .add(commandOpts)
    .add(genericOpts)
    .add(commonOpts)
    .add(addCmdOpts)
    .add(htmlCmdOpts);

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

  // Help
  if (vm.count("help") || commandName.empty()) {
    cout << PROJECT_NAME << ' ' << PROJECT_VERSION << endl;
    cout << "Build: " << __DATE__ << ' ' << __TIME__ << endl;
    cout << PROJECT_COPYRIGHT << endl << endl;

    cout << "Usage: " << argv[0] << " <command> [options]" << endl << endl;
    cout << "Commands:" << endl;
    cout << "  init   Initialize a new wallet" << endl;
    cout << "  add    Add a new entry" << endl;
    cout << "  list   List entries" << endl;
    cout << "  html   Generate HTML output" << endl;
    cout << endl;

    cout << genericOpts << endl;
    cout << commonOpts << endl;
    cout << addCmdOpts << endl;
    cout << htmlCmdOpts << endl;

    return 3;
  }

  // Command Options
  CommandOptions cmdOpts = {};

  if (vm.count("wallet")) {
    cmdOpts.walletPath = vm["wallet"].as<string>();
  }
  if (vm.count("id")) {
    cmdOpts.id = vm["id"].as<string>();
  }
  if (vm.count("title")) {
    cmdOpts.title = vm["title"].as<string>();
  }
  if (vm.count("message")) {
    cmdOpts.title = vm["message"].as<string>();
  }
  if (vm.count("date")) {
    cmdOpts.date = vm["date"].as<string>();
  }
  if (vm.count("revenue")) {
    const string _tmpStr = vm["revenue"].as<string>();

    cmdOpts.revenue = Wallet::Components::stof(_tmpStr);
  }
  if (vm.count("expense")) {
    const string _tmpStr = vm["expense"].as<string>();

    cmdOpts.expense = Wallet::Components::stof(_tmpStr);
  }
  if (vm.count("category")) {
    cmdOpts.category = vm["category"].as<string>();
  }
  if (vm.count("comment")) {
    cmdOpts.comment = vm["comment"].as<string>();
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
  if (vm.count("path")) {
    cmdOpts.path = vm["path"].as<string>();
  }

  // Command Factory
  CommandFactory::setup();
  CommandFactory factory;

  try {
    auto command = factory.makeCommand(commandName);
    command->options = cmdOpts;
    return command->execute();
  }
  catch (const string& e) {
#ifdef TERMCOLOR_HPP_
    cerr << termcolor::on_red << termcolor::white << "ERROR: " << e << termcolor::reset << endl;
#else
    cerr << "ERROR: " << e << endl;
#endif
    return 1;
  }
}

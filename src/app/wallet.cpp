
#include <cstdio>
#include <string>
#include <iostream>
#include <cmath>
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
#include "../class/command_options.hpp"
#include "../class/command_factory.hpp"
#include "../class/command.hpp"

int main(int argc, char* const argv[])
{
  using std::string;
  using std::float_t;
  using std::cout;
  using std::cerr;
  using std::endl;
  using bpo::options_description;
  using bpo::value;
  using Wallet::CommandFactory;
  using Wallet::CommandOptions;

#ifdef DEBUG
  puts("--- DEBUG ---");
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
  //options_description commonOpts("Common options");
  //commonOpts.add_options()
  //            ;

  // Add Command options
  options_description addCmdOpts("Add Command options");
  addCmdOpts.add_options()
              ("id", value<string>()->value_name("string"), "Set a unique ID.")
              ("title,t", value<string>()->value_name("string"), "Set a Title.")
              ("message,m", value<string>()->value_name("string"), "Alias for --title.")
              ("date,d", value<string>()->value_name("string"), "Set a Date. (Format: YYYY-MM-DD)")
              ("revenue,r", value<float_t>()->value_name("number"), "Set a  Revenue.")
              ("expense,e", value<float_t>()->value_name("number"), "Set an Expense.")
              ("category,c", value<string>()->value_name("string"), "Set a Category.")
              ("comment,o", value<string>()->value_name("string"), "Set a Comment.")
              ("interactive,i", "Use some commands interactively.")
              ("force,f", "Force add command. Even if ID is set and already exists.")
              ("no-force", "Do not force add command.");

  options_description opts;
  opts
    .add(commandOpts)
    .add(genericOpts)
    //.add(commonOpts)
    .add(addCmdOpts);

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
    cout << PROJECT_NAME << ' '
         << PROJECT_VERSION_MAJOR << '.' << PROJECT_VERSION_MINOR << '.' << PROJECT_VERSION_PATCH
         << PROJECT_VERSION_APPENDIX << endl;
    cout << PROJECT_COPYRIGHT << endl << endl;

    cout << "Usage: " << argv[0] << " <command> [options]" << endl << endl;
    cout << "Commands:" << endl;
    cout << "  init   Initialize a new wallet" << endl;
    cout << "  add    Add a new entry" << endl;
    cout << endl;

    cout << genericOpts << endl;
    //cout << commonOpts << endl;
    cout << addCmdOpts << endl;

    return 3;
  }

  // Command Options
  CommandOptions cmdOpts = {};

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
    cmdOpts.revenue = vm["revenue"].as<std::float_t>();
  }
  if (vm.count("expense")) {
    cmdOpts.expense = vm["expense"].as<std::float_t>();
  }
  if (vm.count("category")) {
    cmdOpts.category = vm["category"].as<std::string>();
  }
  if (vm.count("comment")) {
    cmdOpts.comment = vm["comment"].as<std::string>();
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

  // Command Factory
  CommandFactory::setup();
  CommandFactory factory;

  try {
    auto command = factory.getCommand(commandName);
    command->setOptions(cmdOpts);
    return command->execute();
  }
  catch (const std::string& e) {
#ifdef TERMCOLOR_HPP_
    cerr << termcolor::on_red << termcolor::white << "ERROR: " << e << termcolor::reset << endl;
#else
    cerr << "ERROR: " << e << endl;
#endif
    return 1;
  }
}


#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>

#ifdef __has_include
#  if __has_include(<filesystem>)
#    include <filesystem>
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
#  else
#     error "Missing <filesystem>"
#  endif
#endif

#include "../config.hpp"
#include "../class/command_factory.hpp"
#include "../class/command.hpp"

//namespace po = boost::program_options;

int main(int argc, char* const argv[])
{
  using std::string;
  using Wallet::CommandFactory, Wallet::CommandOptions;

  printf("%s %d.%d.%d%s\n%s\n",
    PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_APPENDIX,
    PROJECT_COPYRIGHT);

#ifdef DEBUG
  puts("--- DEBUG ---");
#endif
  puts("");

  // Args
  string commandName = "help";

  // Parse args
  //int opt = 0;
  //while ((opt = getopt(argc, argv, "w:?")) != -1) {
  //  printf("opt: %c\n", opt);
  //}

  const CommandOptions cmdOpts = {argv[0]};
  printf("argv0 %p\n", &argv[0]);
  printf("opts  %p\n", &cmdOpts.appPath);

  CommandFactory::setup();
  CommandFactory factory;

  auto command = factory.getCommand(commandName);
  command->setOptions(cmdOpts);
  return command->execute();
}

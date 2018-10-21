
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>

#include "../config.hpp"
#include "../class/command_factory.hpp"

int main(int argc, const char** argv)
{
  printf("%s %d.%d.%d%s\n%s\n",
    PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_APPENDIX,
    PROJECT_COPYRIGHT);

#ifdef DEBUG
  puts("--- DEBUG ---");
#endif
  puts("");

  // Args
  std::string commandName = "help";

  // Parse args
  //int c = 0;
  //while ((c = getopt (argc, argv, "n:t:?")) != -1){
  //}

  Wallet::CommandFactory factory(commandName);
  return factory.execute();
}

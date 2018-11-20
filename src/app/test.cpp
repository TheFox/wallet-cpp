
#ifdef __has_include
#  if __has_include(<catch2/catch.hpp>)
#    define CATCH_CONFIG_MAIN
#    include <catch2/catch.hpp>
#  else
#    error "Missing <catch2/catch.hpp>"
#  endif
#endif // __has_include

#include "config.hpp"

#ifdef CATCH_CONFIG_MAIN
#include "../test/entry_test.hpp"
#else
#include <iostream>
int main(int argc, char* const argv[])
{
  std::cerr << "ERROR: no tests" << std::endl;
  return 1;
}
#endif

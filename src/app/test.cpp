
#ifdef __has_include
#  if __has_include(<catch.hpp>)
#define CATCH_CONFIG_MAIN
#    include <catch.hpp>
//#  else
//#    error "Missing <catch.hpp>"
#  endif
#endif // __has_include

#include "config.hpp"

#ifdef CATCH_CONFIG_MAIN
#else
int main(int argc, char* const argv[])
{}
#endif

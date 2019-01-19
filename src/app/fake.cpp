
#include <cstdio>

#ifdef __has_include
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

int main(int argc, char* const argv[])
{
  printf("--- FAKE ---\n");
  mstch::array a1{};
  printf("a1: %lu\n", a1.size());
}

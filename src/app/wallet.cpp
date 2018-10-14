
#include <cstdio>

#include "../config.hpp"
#include "../components.hpp"

int main(int argc, const char** argv)
{
  printf("%s %d.%d.%d%s\n%s\n",
    PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_APPENDIX,
    PROJECT_COPYRIGHT);
  puts("");

  return 0;
}


#ifndef WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<mstch/mstch.hpp>)
#    include <mstch/mstch.hpp>
#  else
#    error "Missing <mstch/mstch.hpp>"
#  endif
#endif // __has_include

namespace Wallet::Mustache
{
  class BaseMustache : public mstch::object
  {
  public:
    BaseMustache();
    BaseMustache(mstch::array, mstch::map);
    BaseMustache(std::string, mstch::array, mstch::map);

  private:
    // Properties
    const std::string relativePath{"."};
    const mstch::array entries{};
    const mstch::map total{};

    // Functions
    void setup() noexcept;
    mstch::node getProjectName() noexcept;
    mstch::node getProjectHomepageUrl() noexcept;
    mstch::node getProjectVersion() noexcept;
    mstch::node getGeneratedAt() noexcept;
    mstch::node getRelativePath() noexcept;
    mstch::node getCssRelativePath() noexcept;
    mstch::node hasGnuplotSupport() noexcept;

    mstch::node getEntries() noexcept;
    mstch::node getTotal() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_

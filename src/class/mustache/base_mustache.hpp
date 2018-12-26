
#ifndef WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_
#define WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_

#include <string>

#include <mstch/mstch.hpp>

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

    mstch::node getEntries() noexcept;
    mstch::node getTotal() noexcept;
  };
} // Wallet::Mustache Namespace

#endif // WALLETCPP_MUSTACHE_BASE_MUSTACHE_HPP_

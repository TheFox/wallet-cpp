
#include "debug.hpp"
#include "config.hpp"
#include "base_mustache.hpp"
#include "components.hpp"

namespace Wallet::Mustache
{
  BaseMustache::BaseMustache()
  {
    //DLog(" -> BaseMustache::BaseMustache()\n");

    this->setup();
  }

  BaseMustache::BaseMustache(mstch::array _entries, mstch::map _total) :
    entries(std::move(_entries)), total(std::move(_total))
  {
    DLog(" -> BaseMustache::BaseMustache() -> %lu entries, %lu totals\n", this->entries.size(), this->total.size());

    this->setup();
  }

  BaseMustache::BaseMustache(std::string _rel, mstch::array _entries, mstch::map _total) :
    relativePath(std::move(_rel)), entries(std::move(_entries)), total(std::move(_total))
  {
    DLog(" -> BaseMustache::BaseMustache() -> %lu entries, %lu totals\n", this->entries.size(), this->total.size());

    this->setup();
  }

  void BaseMustache::setup() noexcept
  {
    //DLog(" -> BaseMustache::setup()\n");

    this->register_methods(this, {
      {"PROJECT_NAME",         &BaseMustache::getProjectName},
      {"PROJECT_HOMEPAGE_URL", &BaseMustache::getProjectHomepageUrl},
      {"PROJECT_VERSION_FULL", &BaseMustache::getProjectVersionFull},

      {"generated_at",         &BaseMustache::getGeneratedAt},
      {"relative_path",        &BaseMustache::getRelativePath},
      {"css_relative_path",    &BaseMustache::getCssRelativePath},
      {"has_gnuplot_support",  &BaseMustache::hasGnuplotSupport},

      {"entries",              &BaseMustache::getEntries},
      {"total",                &BaseMustache::getTotal},
    });
  }

  mstch::node BaseMustache::getProjectName() noexcept
  {
    return std::string{PROJECT_NAME};
  }

  mstch::node BaseMustache::getProjectHomepageUrl() noexcept
  {
    return std::string{PROJECT_HOMEPAGE_URL};
  }

  mstch::node BaseMustache::getProjectVersionFull() noexcept
  {
    return std::string{PROJECT_VERSION_FULL};
  }

  mstch::node BaseMustache::getGeneratedAt() noexcept
  {
    return Components::getNowStr(WALLETCPP_HUMAN_DATETIME_FORMAT);
  }

  mstch::node BaseMustache::getRelativePath() noexcept
  {
    return this->relativePath;
  }

  mstch::node BaseMustache::getCssRelativePath() noexcept
  {
#ifdef DEBUG
    // tmp/wallet/html relative
    return this->relativePath + "/../../../resources/css";
#else
    return this->getRelativePath();
#endif
  }

  mstch::node BaseMustache::hasGnuplotSupport() noexcept
  {
#ifdef WALLETCPP_GNUPLOT_SUPPORT
    DLog(" -> BaseMustache::hasGnuplotSupport() -> YES\n");
    return true;
#else
    DLog(" -> BaseMustache::hasGnuplotSupport() -> NO\n");
    return false;
#endif
  }

  mstch::node BaseMustache::getEntries() noexcept
  {
    DLog(" -> BaseMustache::getEntries() -> size %lu\n", this->entries.size());
    return this->entries;
  }

  mstch::node BaseMustache::getTotal() noexcept
  {
    //DLog(" -> BaseMustache::getTotal() -> size %lu\n", this->total.size());
    return this->total;
  }
} // Wallet::Mustache Namespace

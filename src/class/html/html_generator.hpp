
#ifndef WALLETCPP_HTML_HTML_GENERATOR_HPP_
#define WALLETCPP_HTML_HTML_GENERATOR_HPP_

#include <string>

#include "fs.hpp"
#include "class/trait/logable.hpp"
#include "class/container/entry_container.hpp"

namespace Wallet::Html
{
  class HtmlGenerator final : public Wallet::Trait::Logable
  {
  public:
    HtmlGenerator(fs::path, fs::path, Wallet::Container::EntryContainer);
    void generate() const;

  private:
    // Variables
    const fs::path yearPath{};
    const fs::path basePath{};
    const fs::path tmpPath{};
    const Wallet::Container::EntryContainer container{};

    // Methods
    void setup() const noexcept;
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_HTML_GENERATOR_HPP_

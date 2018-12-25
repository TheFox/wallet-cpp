
#ifndef WALLETCPP_HTML_HTML_GENERATOR_HPP_
#define WALLETCPP_HTML_HTML_GENERATOR_HPP_

#include <string>

#ifdef __has_include
#  if __has_include(<filesystem>)
#    include <filesystem>
#  elif __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#  else
#    error "Missing <filesystem>"
#  endif
#endif // __has_include

#include "class/container/entry_container.hpp"

namespace Wallet::Html
{
  class HtmlGenerator final
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

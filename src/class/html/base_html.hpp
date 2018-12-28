
#ifndef WALLETCPP_HTML_BASE_HTML_HPP_
#define WALLETCPP_HTML_BASE_HTML_HPP_

#include <string>

#include "fs.hpp"

namespace Wallet::Html
{
  class BaseHtml
  {
  public:
    explicit BaseHtml(fs::path, fs::path, fs::path, std::string);
    const std::string title{};
    std::string getFullPath() const noexcept;
    std::string getFileName() const noexcept;

  protected:
    const fs::path basePath{};
    const fs::path tmpPath{};
    const fs::path fileName{};
  };
} // Wallet::Html Namespace

#endif // WALLETCPP_HTML_BASE_HTML_HPP_

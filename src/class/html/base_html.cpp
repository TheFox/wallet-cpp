
#include "../../debug.hpp"
#include "config.hpp"
#include "base_html.hpp"
#include "../../components.hpp"

namespace Wallet::Html
{
  BaseHtml::BaseHtml(fs::path _path) : path(std::move(_path))
  {
    DLog(" -> BaseHtml::BaseHtml(%s)\n", this->path.c_str());
  }

  CTML::Document BaseHtml::getHtmlDoc(const std::string index) noexcept{
    DLog(" -> BaseHtml::getHtmlDoc(%s)\n", index.c_str());

    CTML::Document document;

    // Head
    document.AppendNodeToHead(
      CTML::Node("meta")
        .SetAttribute("content", "text/html; charset=utf-8")
        .SetAttribute("http-equiv", "Content-Type").UseClosingTag(false));
    document.AppendNodeToHead(CTML::Node("title", std::string{PROJECT_NAME}));
    document.AppendNodeToBody(CTML::Node("h1").AppendChild(
      CTML::Node("a", std::string{PROJECT_NAME}).SetAttribute("href", index)));

    // Signature
    CTML::Node link{"a"};
    link.SetAttribute("href", std::string{PROJECT_HOMEPAGE_URL});
    link.AppendText(std::string{PROJECT_NAME});

    const auto now = Wallet::Components::getNowStr(HUMAN_DATETIME_FORMAT);
    CTML::Node sig{"p", std::string{"Generated @ " + now + " by "}};
    sig.AppendChild(link);
    sig.AppendText(" " PROJECT_VERSION);
    document.AppendNodeToBody(sig);

    return document;
  }
} // Wallet::Html Namespace

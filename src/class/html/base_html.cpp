
#include "../../debug.hpp"
#include "config.hpp"
#include "base_html.hpp"
#include "../../components.hpp"

namespace Wallet { namespace Html
{
  BaseHtml::BaseHtml(boost::filesystem::path _basePath, boost::filesystem::path _fileName, std::string _title) :
    title(std::move(_title)), basePath(std::move(_basePath)), fileName(std::move(_fileName))
  {
    //DLog(" -> BaseHtml::BaseHtml('%s', '%s', '%s')\n", this->basePath.string().c_str(), this->fileName.string().c_str(),
    //  this->title.c_str());
  }

  std::string BaseHtml::getFullPath() const noexcept
  {
    //DLog(" -> BaseHtml::getFullPath()\n");
    return (this->basePath / this->fileName).string();
  }

  std::string BaseHtml::getBasePath() const noexcept
  {
    //DLog(" -> BaseHtml::getBasePath()\n");
    return this->basePath.string();
  }

  std::string BaseHtml::getFileName() const noexcept
  {
    //DLog(" -> BaseHtml::getFileName()\n");
    return this->fileName.string();
  }

  CTML::Document BaseHtml::getHtmlDoc(const std::string index) const noexcept
  {
    //DLog(" -> BaseHtml::getHtmlDoc(%s)\n", index.c_str());

    CTML::Document document;

    // Head
    document.AppendNodeToHead(
      CTML::Node("meta")
        .SetAttribute("content", "text/html; charset=utf-8")
        .SetAttribute("http-equiv", "Content-Type").UseClosingTag(false));
    document.AppendNodeToHead(CTML::Node("title", this->title + " -- " + std::string{PROJECT_NAME}));
    document.AppendNodeToBody(CTML::Node("h1").AppendChild(
      CTML::Node("a", std::string{PROJECT_NAME}).SetAttribute("href", index)));

    // Signature
    CTML::Node link{"a"};
    link.SetAttribute("href", std::string{PROJECT_HOMEPAGE_URL});
    link.AppendText(std::string{PROJECT_NAME});

    const auto now = Components::getNowStr(HUMAN_DATETIME_FORMAT);
    CTML::Node sig{"p", std::string{"Generated @ " + now + " by "}};
    sig.AppendChild(link);
    sig.AppendText(" " PROJECT_VERSION);
    document.AppendNodeToBody(sig);

    return document;
  }
}} // Wallet::Html Namespace

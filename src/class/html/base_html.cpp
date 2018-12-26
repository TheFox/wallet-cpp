
#include "debug.hpp"
#include "base_html.hpp"

namespace Wallet::Html
{
  BaseHtml::BaseHtml(fs::path _basePath, fs::path _tmpPath, fs::path _fileName, std::string _title) :
    title(std::move(_title)), basePath(std::move(_basePath)), tmpPath(std::move(_tmpPath)), fileName(std::move(_fileName))
  {
    //DLog(" -> BaseHtml::BaseHtml('%s', '%s', '%s')\n", this->basePath.string().c_str(), this->fileName.string().c_str(),
    //  this->title.c_str());
  }

  std::string BaseHtml::getFullPath() const noexcept
  {
    return (this->basePath / this->fileName).string();
  }

  std::string BaseHtml::getFileName() const noexcept
  {
    return this->fileName.string();
  }
} // Wallet::Html Namespace

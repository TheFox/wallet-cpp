
#include "debug.hpp"
#include "base_html.hpp"
#include "config.hpp"
#include "components.hpp"

namespace Wallet::Html
{
  BaseMustacheObject::BaseMustacheObject()
  {
    //DLog(" -> BaseMustacheObject::BaseMustacheObject()\n");

    this->setup();
  }

  BaseMustacheObject::BaseMustacheObject(mstch::array _entries, mstch::map _total) :
    entries(std::move(_entries)), total(std::move(_total))
  {
    //DLog(" -> BaseMustacheObject::BaseMustacheObject(mstch::array, mstch::map) -> '%s'\n", this->relativePath.c_str());

    this->setup();
  }

  BaseMustacheObject::BaseMustacheObject(std::string _rel, mstch::array _entries, mstch::map _total) :
    relativePath(std::move(_rel)), entries(std::move(_entries)), total(std::move(_total))
  {
    //DLog(" -> BaseMustacheObject::BaseMustacheObject('%s', mstch::array, mstch::map)\n", this->relativePath.c_str());

    this->setup();
  }

  void BaseMustacheObject::setup() noexcept
  {
    //DLog(" -> BaseMustacheObject::setup()\n");

    this->register_methods(this, {
      {"PROJECT_NAME",         &BaseMustacheObject::getProjectName},
      {"PROJECT_HOMEPAGE_URL", &BaseMustacheObject::getProjectHomepageUrl},
      {"PROJECT_VERSION",      &BaseMustacheObject::getProjectVersion},

      {"generated_at",         &BaseMustacheObject::getGeneratedAt},
      {"relative_path",        &BaseMustacheObject::getRelativePath},
      {"css_relative_path",    &BaseMustacheObject::getCssRelativePath},

      {"entries",              &BaseMustacheObject::getEntries},
      {"total",                &BaseMustacheObject::getTotal},
    });
  }

  mstch::node BaseMustacheObject::getProjectName() noexcept
  {
    return std::string{PROJECT_NAME};
  }

  mstch::node BaseMustacheObject::getProjectHomepageUrl() noexcept
  {
    return std::string{PROJECT_HOMEPAGE_URL};
  }

  mstch::node BaseMustacheObject::getProjectVersion() noexcept
  {
    return std::string{PROJECT_VERSION};
  }

  mstch::node BaseMustacheObject::getGeneratedAt() noexcept
  {
    return Components::getNowStr(HUMAN_DATETIME_FORMAT);
  }

  mstch::node BaseMustacheObject::getRelativePath() noexcept
  {
    return this->relativePath;
  }

  mstch::node BaseMustacheObject::getCssRelativePath() noexcept
  {
#ifdef DEBUG
    return this->relativePath + "/../../resources/css";
#else
    return this->getRelativePath();
#endif
  }

  mstch::node BaseMustacheObject::getEntries() noexcept
  {
    //DLog(" -> BaseMustacheObject::getEntries() -> size %lu\n", this->entries.size());
    return this->entries;
  }

  mstch::node BaseMustacheObject::getTotal() noexcept
  {
    //DLog(" -> BaseMustacheObject::getTotal() -> size %lu\n", this->total.size());
    return this->total;
  }

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

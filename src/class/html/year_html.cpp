
#include "year_html.hpp"
#include "../../debug.hpp"

namespace Wallet::Html
{
  YearHtml::YearHtml(fs::path _path, Wallet::Container::YearEntryContainer _container)
    : BaseHtml{std::move(_path)}, xcontainer(_container)
  {
    DLog(" -> YearHtml::YearHtml(%s)\n", this->path.c_str());
  }

  void YearHtml::generate()
  {
    DLog(" -> YearHtml::generate()\n");
  }
} // Wallet::Html Namespace

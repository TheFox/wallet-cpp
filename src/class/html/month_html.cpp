
#include <fstream> // ofstream

#include "month_html.hpp"
#include "../../debug.hpp"

namespace Wallet::Html
{
  MonthHtml::MonthHtml(std::string _name, fs::path _path, Wallet::Container::MonthEntryContainer _container)
    : BaseHtml{_path / "month.html"}, name(std::move(_name)), basePath(std::move(_path)), container(std::move(_container))
  {
    DLog(" -> MonthHtml::MonthHtml('%s', '%s')\n", this->name.c_str(), this->path.c_str());
  }

  void MonthHtml::generate() const noexcept
  {
    DLog(" -> YearHtml::generate()\n");

    //for (const auto& dayPair : monthContainer.days) {
    //  DLog("     -> day pair\n");
    //  this->htmlOutputDay(dayPair.second);
    //}

    // Month Doc
    auto monthDoc = BaseHtml::getHtmlDoc("../../index.html");
    monthDoc.AppendNodeToBody(
      CTML::Node("h2").AppendText("Month: ").AppendText(this->name));
    //monthDoc.AppendNodeToBody(monthTable);

    // Month File Output
    DLog("     -> write month file: %s\n", this->path.c_str());
    std::ofstream monthFh{};
    monthFh.open(this->path.string(), std::ofstream::out);
    monthFh << monthDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    monthFh.close();
  }
}

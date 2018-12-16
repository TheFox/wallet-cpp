
#include <fstream> // ofstream
#include <iomanip> // setprecision, setfill, setw

#ifdef __has_include
#  if __has_include(<boost/date_time/gregorian/gregorian.hpp>)
#    include <boost/date_time/gregorian/gregorian.hpp>
namespace calendar = boost::gregorian;
#  else
#    error "Missing <boost/date_time/gregorian/gregorian.hpp>"
#  endif
#endif // __has_include

#include "month_html.hpp"
#include "../../debug.hpp"

namespace Wallet::Html
{
  MonthHtml::MonthHtml(fs::path _basePath, Container::MonthPair _map) :
    BaseHtml{std::move(_basePath), fs::path{getMonthFile(_map.first)},
      getMonthName(_map.first) + " " + std::to_string(_map.second.year)},
    name(getMonthName(_map.first)), container(std::move(_map.second)), year(std::to_string(_map.second.year))
  {
    //DLog(" -> MonthHtml::MonthHtml(bp'%s') -> p'%s' n'%s'\n", this->getBasePath().c_str(),
    //  this->getFileName().c_str(), this->name.c_str());
  }

  void MonthHtml::generate() const noexcept
  {
    //DLog(" -> YearHtml::generate()\n");

    // Table Body
    CTML::Node tableBody("tbody");

    std::uint64_t entryCount{};
    for (const auto& dayPair : this->container.days) {
      //DLog("     -> day pair\n");

      for (const auto& entry : dayPair.second.entries) {
        ++entryCount;
        //DLog("     -> entry: %llu %s\n", entryCount, entry.id.c_str());

        // Table Row
        CTML::Node tableTr{"tr"};

        // Table Columns
        tableTr.AppendChild(CTML::Node{"td.left", std::to_string(entryCount)}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.getDateStr()}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.title}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.getRevenueStr()}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.getExpenseStr()}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.getBalanceStr()}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.getCategoryHtml()}.SetAttribute("valign", "top"));
        tableTr.AppendChild(CTML::Node{"td.left", entry.comment}.SetAttribute("valign", "top"));

        // Add TR to Table.
        tableBody.AppendChild(tableTr);
      }
    }

    // Total Row
    CTML::Node totalTr{"tr"};

    // Total Columns
    totalTr.AppendChild(CTML::Node{"td", " "});
    totalTr.AppendChild(CTML::Node{"td", " "});
    totalTr.AppendChild(CTML::Node{"td.left", "TOTAL"});
    totalTr.AppendChild(CTML::Node{"td.right", this->container.getRevenueStr()});
    totalTr.AppendChild(CTML::Node{"td.right red", this->container.getExpenseStr()});
    totalTr.AppendChild(CTML::Node{"td.right", this->container.getBalanceStr()});
    totalTr.AppendChild(CTML::Node{"td", " "});
    totalTr.AppendChild(CTML::Node{"td", " "});

    // Table Head Row
    CTML::Node tableHeadTr{"tr"};

    // Table Head Columns
    tableHeadTr.AppendChild(CTML::Node{"th.left", "#"});
    tableHeadTr.AppendChild(CTML::Node{"th.left", "Date"});
    tableHeadTr.AppendChild(CTML::Node{"th.left", "Title"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Revenue"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Expense"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Balance"});
    tableHeadTr.AppendChild(CTML::Node{"th.right", "Category"});
    tableHeadTr.AppendChild(CTML::Node{"th.left", "Comment"});

    // Table Head
    CTML::Node tableHead{"thead"};
    tableHead.AppendChild(tableHeadTr);

    // Table Footer
    CTML::Node tableFoot{"tfoot"};
    tableFoot.AppendChild(totalTr);

    // Table
    CTML::Node table{"table.list"};
    table.SetAttribute("border", "1"); // TODO
    table.AppendChild(tableHead);
    table.AppendChild(tableBody);
    table.AppendChild(tableFoot);

    // Month Doc
    auto monthDoc = this->getHtmlDoc("../../index.html");
    monthDoc.AppendNodeToBody(
      CTML::Node{"h2"}.AppendText("Month: " + this->name + " ").AppendChild(
        CTML::Node{"a", this->year}.SetAttribute("href", "index.html")));
    monthDoc.AppendNodeToBody(table);

    // Month File Output
    //DLog("     -> write month file: %s\n", this->getFullPath().c_str());
    std::ofstream monthFh{};
    monthFh.open(this->getFullPath(), std::ofstream::out);
    monthFh << monthDoc.ToString(CTML::StringFormatting::MULTIPLE_LINES); // TODO
    monthFh.close();
  }

  std::string MonthHtml::getMonthFile(const Container::ContainerMonth month) noexcept
  {
    std::stringstream ss{};
    ss << "month_";
    ss << std::setfill('0') << std::setw(2) << std::to_string(month);
    ss << ".html";
    return ss.str();
  }

  std::string MonthHtml::getMonthName(const Container::ContainerMonth _month) noexcept
  {
    calendar::greg_month month{_month};
    return month.as_long_string();
  }
}


#include <fstream> // ofstream
#include <string>
#include <iterator> // back_inserter
#include <algorithm> // transform

#include "debug.hpp"
#include "components.hpp"
#include "year_html.hpp"
#include "month_html.hpp"

namespace Wallet::Html
{
  YearMustacheObject::YearMustacheObject(std::string _rel, mstch::array _entries, mstch::map _total,
                                         std::string _year, Container::CategoryArray _categoryNames) :
    BaseMustacheObject(std::move(_rel), std::move(_entries), std::move(_total)), year(std::move(_year)),
    categoryNames(std::move(_categoryNames))
  {
    DLog(" -> YearMustacheObject::YearMustacheObject('%s', '%s', %lu)\n",
      _rel.c_str(), this->year.c_str(), _categoryNames.size());

    this->register_methods(this, {
      {"year",           &YearMustacheObject::getYear},
      {"category_count", &YearMustacheObject::getCategoryCount},
      {"categories",     &YearMustacheObject::getCategories},
    });
  }

  mstch::node YearMustacheObject::getYear() noexcept
  {
    DLog(" -> YearMustacheObject::getYear()\n");
    return this->year;
  }

  mstch::node YearMustacheObject::getCategoryCount() noexcept
  {
    DLog(" -> YearMustacheObject::getCategoryCount() -> %lu\n", this->categoryNames.size());
    //return std::string{"1"};
    //return this->categoryNames.size();
    return std::to_string(this->categoryNames.size());
  }

  mstch::node YearMustacheObject::getCategories() noexcept
  {
    DLog(" -> YearMustacheObject::getCategories() -> %lu\n", this->categoryNames.size());

    // Cache
    //if (this->hasMappedCategoryNames) {
    //  return this->mappedCategoryNames;
    //}
    //this->hasMappedCategoryNames = true;

    // Iterators
    const auto cnb = this->categoryNames.cbegin();
    const auto cne = this->categoryNames.cend();

    mstch::array names{};

    // Transform vector of names to map with 'name' property.
    std::transform(cnb, cne, std::back_inserter(names), [](std::string name) {
      //DLog(" -> transform: '%s'\n", name.c_str());
      return mstch::map{
        {"name", std::move(name)},
      };
    });

    return names;
  }

  YearHtml::YearHtml(fs::path _basePath, Wallet::Container::YearEntryContainer _container) :
    BaseHtml{std::move(_basePath), fs::path{"index.html"}, "Year " + std::to_string(_container.year)},
    container(std::move(_container))
  {
    DLog(" -> YearHtml::YearHtml('%s', '%s')\n", this->basePath.c_str(), this->getFileName().c_str());
  }

  void YearHtml::generate() const
  {
    DLog(" -> YearHtml::generate() -> %d\n", this->container.year);

    if (!fs::exists(WALLETCPP_YEAR_VIEW_PATH)) {
      throw std::string{"Year template file does not exists: "} + WALLETCPP_YEAR_VIEW_PATH;
    }

    // Category Names
    Container::CategoryArray categoryNames{};

    // https://thispointer.com/how-to-copy-all-values-from-a-map-to-a-vector-in-c/
    std::transform(this->container.categories.cbegin(), this->container.categories.cend(),
      std::back_inserter(categoryNames),
      [](const auto& pair) {
        return pair.first;
      });

    // Table Body
    mstch::array entries{};

    // Categories Iterators
    const auto cib = this->container.categories.cbegin();
    const auto cie = this->container.categories.cend();

    for (const auto& monthPair : this->container.months) {
      MonthHtml monthHtml{this->basePath, monthPair};
      //monthHtml.generate(); // TODO

      // Match common categories to month categories.
      mstch::array monthCategories{};
      std::transform(cib, cie, std::back_inserter(monthCategories), [&monthPair](const auto& pair) {
        std::string balance{"&nbsp;"};
        std::string balanceClass{};

        try {
          // Search by key (Name).
          const auto& category = monthPair.second.categories.at(pair.first);
          DLog(" -> category found: '%s'\n", pair.first.c_str());

          balance = category.getBalanceStr();
          balanceClass = category.getBalanceHtmlClass();
        } catch (const std::out_of_range& exception) {
          DLog(" -> nothing found for category '%s'\n", pair.first.c_str());
        }

        return mstch::map{
          {"balance",       std::move(balance)},
          {"balance_class", std::move(balanceClass)},
        };
      });

      mstch::map monthMap{
        {"file_name",        monthHtml.getFileName()},
        {"month_name",       monthHtml.name},
        {"revenue",          monthPair.second.getRevenueStr()},
        {"expense",          monthPair.second.getExpenseStr()},
        {"balance",          monthPair.second.getBalanceStr()},
        {"balance_class",    monthPair.second.getBalanceHtmlClass()},
        {"month_categories", std::move(monthCategories)},
      };
      entries.push_back(monthMap);
    } // this->container.months

    // Match common categories to total month categories.
    mstch::array monthCategories{};
    std::transform(cib, cie, std::back_inserter(monthCategories), [&](const auto& pair) {
      DLog(" -> category: '%s'\n", pair.first.c_str());

      return mstch::map{
        {"balance",       pair.second.getBalanceStr()},
        {"balance_class", pair.second.getBalanceHtmlClass()},
      };
    });

    const std::string tpl = Components::readFileIntoString(WALLETCPP_YEAR_VIEW_PATH);

    const auto yearStr = std::to_string(this->container.year);

    const mstch::map total{
      {"year",             std::string{"TOTAL"}},
      {"revenue",          this->container.getRevenueStr()},
      {"expense",          this->container.getExpenseStr()},
      {"balance",          this->container.getBalanceStr()},
      {"balance_class",    this->container.getBalanceHtmlClass()},
      {"month_categories", std::move(monthCategories)},
    };

    const auto context = std::make_shared<YearMustacheObject>("../..", entries, total, yearStr, categoryNames);

    // Output: index.html
    std::ofstream indexFh{this->getFullPath()};
    indexFh << mstch::render(tpl, context);
    indexFh.close();
  }
} // Wallet::Html Namespace

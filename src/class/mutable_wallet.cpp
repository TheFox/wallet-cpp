
#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>
#include <iostream>
#include <cstdint>

#include "config.hpp"
#include "mutable_wallet.hpp"
#include "entry.hpp"
#include "entry_container.hpp"
#include "../components.hpp"

namespace Wallet
{
  MutableWallet::MutableWallet(const std::string path) noexcept : path(path)
  {
#ifdef DEBUG
    printf(" -> MutableWallet::MutableWallet\n");
#endif
  }

  MutableWallet::~MutableWallet() noexcept(noexcept(this->saveIndex()) && noexcept(this->removeLock()))
  {
#ifdef DEBUG
    printf(" -> MutableWallet::~MutableWallet\n");
#endif

    this->saveIndex();
    this->removeLock();
  }

  void MutableWallet::setup()
  {
    this->setup(false);
  }

  void MutableWallet::setup(const bool explicitInit)
  {
    this->setupVariables();
#ifdef NDEBUG
    this->createLock();
#endif
    this->setupDirectories(explicitInit);
  }

  bool MutableWallet::add(const Entry entry, const bool isUnique)
  {
    using YAML::Node;
    using YAML::NodeType;

#ifdef DEBUG
    printf(" -> MutableWallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    const bool entryExists = this->entryExists(entry);
    if (isUnique && entryExists) {
      return false;
    }

    this->isIndexModified = true;
    this->index["index"].push_back(entry.id);

    // Month File
    const auto monthFile = entry.getFileName();
    const auto monthFilePath = this->dataPath / monthFile;
    auto& monthFilePathStr = monthFilePath.string();

    // For 'updated_at' field.
    const auto now = Components::getNowStr();

    Node month;
    if (fs::exists(monthFilePathStr)) {
#ifdef DEBUG
      printf(" -> load month file: %s\n", monthFilePathStr.c_str());
#endif

      // Load YAML file.
      month = YAML::LoadFile(monthFilePathStr);

      // Update file version.
      const auto _version = month["meta"]["version"].as<int>();
      if (_version == 1) {
        month["meta"]["version"] = WALLET_MONTH_FILE_VERSION;
      }

      // Updated At
      month["meta"]["updated_at"] = now;
    } else {
#ifdef DEBUG
      printf(" -> create month file: %s\n", monthFilePathStr.c_str());
#endif

      // Create new meta data.
      Node meta(NodeType::Map);
      meta["version"] = WALLET_MONTH_FILE_VERSION;
      meta["created_at"] = now;
      meta["updated_at"] = now;

      // Add Meta to month file.
      month["meta"] = meta;

      // Create new days map.
      Node days(NodeType::Map);
      month["days"] = days;
    }

    // Create day sequence.
    const std::string dayStr = entry.getDateStr();
    if (!month["days"][dayStr]) {
#ifdef DEBUG
      printf(" -> create new day: %s\n", entry.getDateStr().c_str());
#endif
      Node day(NodeType::Sequence);
      month["days"][dayStr] = day;
    }

    // Convert Entry to Node.
    const auto node = entry.as<Node>();
    month["days"][dayStr].push_back(node);

    // Save Month file.
    std::ofstream fout(monthFilePathStr);
    fout << month;
    fout.close();

    return true;
  }

  Container::EntryContainer MutableWallet::getEntries(const Components::Date date) const
  {
#ifdef DEBUG
    printf(" -> MutableWallet::getEntries(%d, %d, %d)\n", date.year, date.month, date.day);
#endif

    Container::EntryContainer container{};

    if (!fs::exists(this->dataPath)) {
      throw std::string{"Wallet does not exists."};
    }

    const bool hasYear = date.year != 0;
    const bool hasMonth = date.month != 0;
    const bool hasDay = date.day != 0;

    // Iterate files.
    for (auto& directoryItem : fs::directory_iterator(this->dataPath)) {
      const auto& filePath = directoryItem.path();
      const auto& fileStr = filePath.string();
      const auto fileNameStr = filePath.filename().string();

      // Check correct file.
      if (fileNameStr.length() < 17
        || fileNameStr.substr(0, 6) != "month_"
        || fileStr.substr(fileStr.size() - 4) != ".yml") {
        continue;
      }

      // Filter Year.
      if (hasYear) {
        const auto filePathYearInt = static_cast<decltype(date.year)>(std::stoi(fileNameStr.substr(6, 4)));
        if (filePathYearInt != date.year) {
          continue;
        }
      }

      // Filter Month.
      if (hasMonth) {
        const auto filePathMonthInt = static_cast<decltype(date.month)>(std::stoi(fileNameStr.substr(11, 2)));
        if (filePathMonthInt != date.month) {
          continue;
        }
      }

      // Read month file.
      auto yaml = YAML::LoadFile(fileStr);

      // Iterate days.
      for (const auto& dayNode : yaml["days"]) {
        const auto dayStr = dayNode.first.as<std::string>();
        const auto year = static_cast<std::uint16_t>(std::stoi(dayStr.substr(0, 4)));
        const auto month = static_cast<std::uint8_t>(std::stoi(dayStr.substr(5, 2)));
        const auto day = static_cast<std::uint8_t>(std::stoi(dayStr.substr(8)));
        const auto node = dayNode.second;

        if (hasDay) {
          const auto parsedDay = Components::parseDate(dayStr);
          if (parsedDay.day != date.day) {
            continue;
          }
        }

        // Container
        container.dayCount++;

        // Year
        auto& yearMap = container.years[year];
        yearMap.dayCount++;
        if (yearMap.year == 0) {
          yearMap.year = year;
        }

        // Month
        auto& monthMap = yearMap.months[month];
        monthMap.dayCount++;
        if (monthMap.month == 0) {
          monthMap.month = month;
        }

        // Day
        auto& dayMap = monthMap.days[day];
        dayMap.dayCount++;
        if (dayMap.day == 0) {
          dayMap.day = day;
        }

        // Iterate Day entries.
        for (const auto& entryNode : node) {
          // emplace_back() is Nice!!
          const auto entry = dayMap.entries.emplace_back(entryNode);

          // Container
          container.entryCount++;
          container.revenue += entry.getRevenue();
          container.expense += entry.getExpense();
          container.balance += entry.getBalance();

          // Year
          yearMap.entryCount++;
          yearMap.revenue += entry.getRevenue();
          yearMap.expense += entry.getExpense();
          yearMap.balance += entry.getBalance();

          // Month
          monthMap.entryCount++;
          monthMap.revenue += entry.getRevenue();
          monthMap.expense += entry.getExpense();
          monthMap.balance += entry.getBalance();

          // Day
          dayMap.entryCount++;
          dayMap.revenue += entry.getRevenue();
          dayMap.expense += entry.getExpense();
          dayMap.balance += entry.getBalance();
        } // Day Entries
      } // Days
    } // Files

    return container;
  }

  // void MutableWallet::htmlOutput(const std::optional<std::string>& _path) const noexcept
  void MutableWallet::htmlOutput(const std::string& _path) const noexcept
  {
    using fs::create_directories;
    using fs::exists;
    using std::string;

#ifdef DEBUG
    printf(" -> MutableWallet::htmlOutput()\n");
    // printf(" -> MutableWallet::htmlOutput('%s')\n", _path.has_value() ? _path.value().c_str() : "");
#endif

    const auto& container = this->getEntries({0, 0, 0});

    // if (_path.has_value()) {
    //   this->htmlPath = _path.value();
    if (_path.size() > 0) {
      this->htmlPath = _path;
    } else {
      this->htmlPath = this->path / "html";
    }

    // Directory
    if (!exists(this->htmlPath)) {
      create_directories(this->htmlPath);
      create_directories(this->htmlPath / "year");
    }

    // TODO: copy css file to html dir

    CTML::Node tableBody("tbody");

    for (const auto& yearPair : container.years) {
#ifdef DEBUG
      std::cout << "year pair: " << yearPair.first << std::endl;
#endif
      this->htmlOutputYear(yearPair.second);

      CTML::Node tableRow{"tr"};
      tableRow.AppendChild(CTML::Node("td.left").AppendChild(CTML::Node("a").SetAttribute("href", "year/" + std::to_string(yearPair.first)).SetContent(std::to_string(yearPair.first))));
      tableBody.AppendChild(tableRow);
    }

    // Index Table Head
    CTML::Node indexTableHeadTr{"tr"};
    indexTableHeadTr.AppendChild(CTML::Node("th.left", "Year"));
    indexTableHeadTr.AppendChild(CTML::Node("th.right", "Revenue"));
    indexTableHeadTr.AppendChild(CTML::Node("th.right", "Expense"));
    indexTableHeadTr.AppendChild(CTML::Node("th.right", "Balance"));
    indexTableHeadTr.AppendChild(CTML::Node("th.right", "Balance &#8721;"));

    CTML::Node indexTableHead{"thead"};
    indexTableHead.AppendChild(indexTableHeadTr);

    // Index Table
    CTML::Node indexTable{"table.list"};
    indexTable.AppendChild(indexTableHead);
    indexTable.AppendChild(tableBody);

    // Index Doc
    CTML::Document indexDoc;
    indexDoc.AddNodeToHead(
      CTML::Node("meta").SetAttribute("content", "text/html; charset=utf-8").SetAttribute("http-equiv",
        "Content-Type").UseClosingTag(false));
    indexDoc.AddNodeToHead(CTML::Node("title", string{PROJECT_NAME}));
    indexDoc.AddNodeToBody(CTML::Node("h1").AppendChild(
      CTML::Node("a").SetContent(string{PROJECT_NAME}).SetAttribute("href", "./index.html")));
    indexDoc.AddNodeToBody(this->getHtmlSignatur());
    indexDoc.AddNodeToBody(indexTable);

    // Output: index.html
    std::ofstream indexFh;
    indexFh.open((this->htmlPath / "index.html").string(), std::ofstream::out);
    indexFh << indexDoc.ToString(CTML::Readability::MULTILINE); // TODO
    indexFh.close();
  }

  void MutableWallet::htmlOutputYear(const Container::YearEntryContainer& yearContainer) const noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::htmlOutputYear()\n");
#endif

    for (const auto& monthPair : yearContainer.months) {
#ifdef DEBUG
      std::cout << "month pair" << std::endl;
#endif
      this->htmlOutputMonth(monthPair.second);
    }
  }

  void MutableWallet::htmlOutputMonth(const Container::MonthEntryContainer& monthContainer) const noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::htmlOutputMonth()\n");
#endif

    for (const auto& dayPair : monthContainer.days) {
#ifdef DEBUG
      std::cout << "day pair" << std::endl;
#endif
      this->htmlOutputDay(dayPair.second);
    }
  }

  void MutableWallet::htmlOutputDay(const Container::DayEntryContainer& dayContainer) const noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::htmlOutputDay()\n");
#endif

    for (const auto& entry : dayContainer.entries) {
#ifdef DEBUG
      std::cout << "entry " << entry.id << std::endl;
#endif
    }
  }

  CTML::Node MutableWallet::getHtmlSignatur() const noexcept
  {
    CTML::Node link{"a"};
    link.SetAttribute("href", std::string{PROJECT_HOMEPAGE_URL});
    link.SetContent(std::string{PROJECT_NAME} + " " + PROJECT_VERSION);

    const auto now = Components::getNowStr(HUMAN_DATETIME_FORMAT);
    CTML::Node sig{"p", std::string{"Generated @ " + now + " by "}};
    sig.AppendChild(link);
    return sig;
  }

  void MutableWallet::setupVariables() noexcept
  {
    this->dataPath = this->path / "data";
    this->indexPath = this->dataPath / "index.yml";
    this->tmpPath = this->path / "tmp";
    this->lockPath = this->tmpPath / "lock";

    this->isLocked = false;
    this->isIndexLoaded = false;
    this->isIndexModified = false;
  }

  void MutableWallet::setupDirectories(const bool explicitInit) noexcept
  {
    using std::cout;
    using std::endl;
    using std::ofstream;
    using std::ifstream;
    using fs::exists;
    using fs::path;
    using fs::create_directories;

    // Make main directory.
    if (exists(this->path)) {
      if (explicitInit) {
        cout << "Wallet already exists at " << this->path << '.' << endl;
      }
    } else {
      if (explicitInit) {
        cout << "Create wallet at " << this->path << '.' << endl;
      }
      create_directories(this->path);
    }

    // Make data/ directory.
    if (!exists(this->dataPath)) {
      create_directories(this->dataPath);
    }

    // Make tmp/ directory.
    if (!exists(this->tmpPath)) {
      create_directories(this->tmpPath);
    }

    const path versionFile = this->path / "version";
    ifstream iVersionFh;
    decltype(this->version) oldVersion{0};
    if (exists(versionFile)) {
      iVersionFh.open(versionFile.string(), ofstream::in);
      iVersionFh >> oldVersion;
      iVersionFh.close();
    }

    if (this->version > oldVersion) {
      ofstream oVersionFh;
      oVersionFh.open(versionFile.string(), ofstream::out);
      oVersionFh << this->version;
      oVersionFh.close();
    }

    // Create main .gitignore file.
    const path gitignoreFile = this->path / ".gitignore";
    if (!exists(gitignoreFile)) {
      ofstream gitignoreFh;
      gitignoreFh.open(gitignoreFile.string(), ofstream::out);
      gitignoreFh << "/tmp/" << '\n';
      gitignoreFh << "/html/" << '\n';
      gitignoreFh.close();
    }

    // Remove old tmp/.gitignore file.
    const path oldGitignoreFile = this->tmpPath / ".gitignore";
    if (exists(oldGitignoreFile)) {
      fs::remove(oldGitignoreFile);
    }
  }

  void MutableWallet::createLock()
  {
#ifdef DEBUG
    printf(" -> MutableWallet::createLock\n");
#endif

    // Already locked.
    if (this->isLocked) {
      return;
    }

    if (fs::exists(this->lockPath)) {
      throw std::string{"Wallet is locked."};
    }

    // Create lock file.
    std::ofstream lockFh(this->lockPath.string());
    lockFh << "locked";
    lockFh.close();

    this->isLocked = true;
  }

  void MutableWallet::removeLock() noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::removeLock\n");
#endif

    if (!this->isLocked) {
      return;
    }

    // Remove lock file.
    const auto _lockPath = this->lockPath.string();
    if (fs::exists(_lockPath)) {
      fs::remove(_lockPath);
    }

    this->isLocked = false;
  }

  void MutableWallet::loadIndex() noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::loadIndex\n");
#endif

    if (this->isIndexLoaded) {
      return;
    }
    this->isIndexLoaded = true;

    if (fs::exists(this->indexPath)) {
      // Load YAML file.
      this->index = YAML::LoadFile(this->indexPath.string());
    } else {
      // Create new index.
      this->isIndexModified = true;
    }

    auto idx = this->index["index"];
    if (!idx || !idx.IsDefined()) {
      this->isIndexModified = true;

      // Create new 'index' sequence.
      YAML::Node _idx(YAML::NodeType::Sequence);
      _idx.push_back("hello_world");
      this->index["index"] = _idx;
    }
  }

  /**
   * Save the index to file.
   */
  void MutableWallet::saveIndex() noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::saveIndex\n");
#endif

    // Skip function when nothing has been changed.
    if (!this->isIndexModified) {
      return;
    }
    this->isIndexModified = false;

    std::ofstream fout(this->indexPath.string());
    fout << this->index;
    fout.close();
  }

  /**
   * Check entry exists.
   */
  bool MutableWallet::entryExists(const Entry& entry) noexcept
  {
#ifdef DEBUG
    printf(" -> MutableWallet::entryExists\n");
#endif

    this->loadIndex();

    const auto _b = this->index["index"].begin();
    const auto _e = this->index["index"].end();

    auto it = std::find_if(_b, _e, [&](const auto& item) {
      return item.template as<std::string>() == entry.id;
    });

    return it != _e;
  }
} // Wallet Namespace

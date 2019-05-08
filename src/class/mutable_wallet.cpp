
#include <fstream> // ofstream, ifstream
#include <iostream>
#include <cstdint>
#include <cstdio> // remove

#ifdef __has_include
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#    error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "debug.hpp"
#include "components.hpp"
#include "mutable_wallet.hpp"
#include "entry.hpp"
#include "container/entry_container.hpp"
#include "html/html_generator.hpp"

namespace Wallet
{
  MutableWallet::MutableWallet(std::string _path) noexcept :
    path(_path),
    dataPath(this->path / "data"),
    indexPath(this->dataPath / "index.yml"),
    epicsPath(this->dataPath / "epics.yml"),
    tmpPath(this->path / "tmp"),
    lockPath(this->tmpPath / "lock")
  {
    DLog(" -> MutableWallet::MutableWallet('%s')\n", this->path.c_str());
  }

  MutableWallet::~MutableWallet() noexcept
  {
    DLog(" -> MutableWallet::~MutableWallet()\n");

    this->saveIndex();
    this->saveEpics();
    this->removeLock();
  }

  void MutableWallet::init() noexcept{
    DLog(" -> MutableWallet::init()\n");

    // Make main directory.
    if (fs::exists(this->path)) {
      std::cout << "Wallet already exists at " << this->path << '.' << std::endl;
    } else {
      std::cout << "Create wallet at " << this->path << '.' << std::endl;
      fs::create_directories(this->path);
    }

    this->setup();
  }

  bool MutableWallet::add(const Entry& entry, const bool isUnique)
  {
    DLog(" -> MutableWallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');

    this->setup();

    if (isUnique && this->entryExists(entry)) {
      return false;
    }

    this->isIndexModified = true;
    this->index["index"].push_back(entry.id);

    // Month File
    const auto monthFile = entry.getFileName();
    const auto monthFilePath = this->dataPath / monthFile;
    const auto& monthFilePathStr = monthFilePath.string();

    // For 'updated_at' field.
    const auto now = Components::getNowStr();

    YAML::Node month{};
    if (fs::exists(monthFilePathStr)) {
      DLog(" -> load month file: %s\n", monthFilePathStr.c_str());

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
      DLog(" -> create month file: %s\n", monthFilePathStr.c_str());

      // Create new meta data.
      YAML::Node meta{YAML::NodeType::Map};
      meta["version"] = WALLET_MONTH_FILE_VERSION;
      meta["created_at"] = now;
      meta["updated_at"] = now;

      // Add Meta to month file.
      month["meta"] = meta;

      // Create new days map.
      YAML::Node days{YAML::NodeType::Map};
      month["days"] = days;
    }

    // Create day sequence.
    const auto dayStr = entry.getDateStr();
    if (!month["days"][dayStr]) {
      DLog(" -> create new day: %s\n", entry.getDateStr().c_str());

      YAML::Node day{YAML::NodeType::Sequence};
      month["days"][dayStr] = day;
    }

    // Convert Entry to Node.
    const auto node = entry.as<YAML::Node>();

    // Add Entry Node to array.
    month["days"][dayStr].push_back(node);

    // Save Month file.
    std::ofstream fout{monthFilePathStr};
    fout << month << '\n';
    fout.close();

    return true;
  }

  // TODO: filter empty days, months, years
  Container::EntryContainer MutableWallet::getEntries(const Components::Date& date, const std::string& category, const std::string& epic) const
  {
    DLog(" -> MutableWallet::getEntries(%d, %d, %d, '%s', '%s')\n", date.year, date.month, date.day, category.c_str(), epic.c_str());

    // Log
    this->log("[wallet] get entries");

    Container::EntryContainer container{};

    if (!fs::exists(this->dataPath)) {
      throw std::string{"Wallet does not exists or is corrupt."};
    }

    const bool hasYear = date.year != 0;
    const bool hasMonth = date.month != 0;
    const bool hasDay = date.day != 0;
    const bool hasCategory = !category.empty();
    const bool hasEpic = !epic.empty();

    DLog(" -> MutableWallet::getEntries() -> has category: %c\n", hasCategory ? 'Y' : 'N');
    DLog(" -> MutableWallet::getEntries() -> has epic: %c\n", hasEpic ? 'Y' : 'N');

    // Iterate files (= months).
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
        const auto fileYear = fileNameStr.substr(6, 4);
        const auto filePathYearInt = static_cast<decltype(date.year)>(std::stoi(fileYear));
        if (filePathYearInt != date.year) {
          continue;
        }
      }

      // Filter Month.
      if (hasMonth) {
        const auto fileMonth = fileNameStr.substr(11, 2);
        const auto filePathMonthInt = static_cast<decltype(date.month)>(std::stoi(fileMonth));
        if (filePathMonthInt != date.month) {
          continue;
        }
      }

      // Read month file.
      auto yaml = YAML::LoadFile(fileStr);

      // Iterate days.
      for (const auto& dayNode : yaml["days"]) {
        const auto dayStr = dayNode.first.as<std::string>();
        const auto year = static_cast<Container::ContainerYear>(std::stoi(dayStr.substr(0, 4)));
        const auto month = static_cast<Container::ContainerMonth>(std::stoi(dayStr.substr(5, 2)));
        const auto day = static_cast<Container::ContainerDay>(std::stoi(dayStr.substr(8)));
        const auto node = dayNode.second;

        // Filter Day
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
        if (monthMap.year == 0) {
          monthMap.year = year;
        }
        if (monthMap.fileName.empty()) {
          monthMap.fileName = fileNameStr;
        }
        if (monthMap.yearMonth.empty()) {
          monthMap.yearMonth = dayStr.substr(0, 4) + "-" + dayStr.substr(5, 2);
        }

        // Day
        auto& dayMap = monthMap.days[day];
        dayMap.dayCount++;
        if (dayMap.day == 0) {
          dayMap.day = day;
        }

        // Iterate Day entries.
        for (const auto& entryNode : node) {
          const Entry entry{entryNode};

          // Filter Category.
          if (hasCategory) {
            DLog(" -> MutableWallet::getEntries() -> compare category: %d '%s' '%s'\n", entry.category.compare(category), entry.category.c_str(), category.c_str());
            if (entry.category.compare(category) != 0) {
              DLog(" -> MutableWallet::getEntries() -> skip, category not equal\n");
              continue;
            }
          }

          // Filter Epic.
          if (hasEpic) {
            DLog(" -> MutableWallet::getEntries() -> compare epic: %d '%s' '%s'\n", entry.epic.compare(epic), entry.epic.c_str(), epic.c_str());
            if (entry.epic.compare(epic) != 0) {
              DLog(" -> MutableWallet::getEntries() -> skip, epic not equal\n");
              continue;
            }
          }

          // Add entry to array.
          dayMap.entries.push_back(entry);

          // Default Epic
          std::string entityEpic{"default"};
          if (!entry.epic.empty()) {
            entityEpic = entry.epic;
          }

          // Container
          container.entryCount++;
          container.revenue += entry.revenue;
          container.expense += entry.expense;
          container.balance += entry.balance;

          // Year
          yearMap.entryCount++;
          yearMap.revenue += entry.revenue;
          yearMap.expense += entry.expense;
          yearMap.balance += entry.balance;

          // Year Category
          auto& ycategory = yearMap.categories[entry.category];
          ycategory.revenue += entry.revenue;
          ycategory.expense += entry.expense;
          ycategory.balance += entry.balance;

          // Year Epic
          auto& yepic = yearMap.epics[entityEpic];
          yepic.revenue += entry.revenue;
          yepic.expense += entry.expense;
          yepic.balance += entry.balance;

          // Month
          monthMap.entryCount++;
          monthMap.revenue += entry.revenue;
          monthMap.expense += entry.expense;
          monthMap.balance += entry.balance;

          // Month Category
          auto& mcategory = monthMap.categories[entry.category];
          mcategory.revenue += entry.revenue;
          mcategory.expense += entry.expense;
          mcategory.balance += entry.balance;

          // Month Epic
          auto& mepic = monthMap.epics[entityEpic];
          mepic.revenue += entry.revenue;
          mepic.expense += entry.expense;
          mepic.balance += entry.balance;

          // Day
          dayMap.entryCount++;
          dayMap.revenue += entry.revenue;
          dayMap.expense += entry.expense;
          dayMap.balance += entry.balance;
        } // Day Entries
      } // Days
    } // Files

    return container;
  }

  // TODO: date
  void MutableWallet::htmlOutput(const std::string& _path,
    const std::string& category, const std::string& epic) const
  {
    DLog(" -> MutableWallet::htmlOutput('%s', '%s', '%s')\n",
      _path.c_str(), category.c_str(), epic.c_str());
    this->log("[wallet] generate html files");

    const auto& container = this->getEntries({0, 0, 0}, category, epic);
    DLog(" -> MutableWallet::htmlOutput() -> container %p\n", &container);

    fs::path htmlPath{};
    if (_path.empty()) {
      htmlPath = this->path / "html";
    } else {
      htmlPath = _path;
    }

    const Wallet::Html::HtmlGenerator htmlGenerator{htmlPath, this->tmpPath, container};
    htmlGenerator.logLevel = this->logLevel;
    htmlGenerator.generate();
  }

  void MutableWallet::addEpic(const Epic& epic) noexcept
  {
    DLog(" -> MutableWallet::addEpic()\n");

    this->loadEpics();

    // Convert Epic to Node.
    const auto node = epic.as<YAML::Node>();

    // Add Epic Node to array.
    this->epics["epics"].push_back(node);

    this->areEpicsModified = true;
  }

  void MutableWallet::removeEpic(const Epic& epic) noexcept
  {
    DLog(" -> MutableWallet::removeEpic()\n");

    this->loadEpics();

    const auto epicsOriginal = std::move(this->epics["epics"]);
    YAML::Node epicsNew{YAML::NodeType::Sequence};

    // TODO use std lib here instead of loop
    for (const auto& node : epicsOriginal) {
      DLog(" -> MutableWallet::removeEpic() -> node '%s'\n", node["handle"].as<std::string>().c_str());

      if (node["handle"].as<std::string>() != epic.handle) {
        DLog(" -> MutableWallet::removeEpic() -> keep node\n");
        epicsNew.push_back(node);
      }
    }

    this->epics["epics"] = std::move(epicsNew);
    this->areEpicsModified = true;
    DLog(" -> MutableWallet::removeEpic() END\n");
  }

  Epic MutableWallet::getEpicByHandle(const std::string& handle)
  {
    DLog(" -> MutableWallet::getEpicByHandle() -> handle '%s'\n", handle.c_str());

    this->loadEpics();

    const auto _begin = this->epics["epics"].begin();
    const auto _end = this->epics["epics"].end();

    const auto it = std::find_if(_begin, _end, [&handle](const auto& item) {
      DLog(" -> MutableWallet::getEpicByHandle() -> find '%s'\n", handle.c_str());
      //DLog(" -> MutableWallet::getEpicByHandle() -> find '%s'\n", item["handle"].as<std::string>().c_str());
      return item["handle"].template as<std::string>() == handle;
    });

    DLog(" -> MutableWallet::epicExists() -> found: %c\n", it != _end ? 'Y' : 'N');

    if (it == _end) {
      throw std::string{"No Epic found: "} + handle;
    }

    Epic epic{*it};
    return epic;
  }

  void MutableWallet::setup()
  {
    DLog(" -> MutableWallet::setup()\n");

    if (this->hasSetup)
      return;
    this->hasSetup = true;

//#ifdef NDEBUG
    this->createLock();
//#endif
    this->setupDirectories();
  }

  void MutableWallet::setupDirectories() noexcept
  {
    // Make main directory.
    if (!fs::exists(this->path)) {
      fs::create_directories(this->path);
    }

    // Make data/ directory.
    if (!fs::exists(this->dataPath)) {
      fs::create_directories(this->dataPath);
    }

    // Make tmp/ directory.
    if (!fs::exists(this->tmpPath)) {
      fs::create_directories(this->tmpPath);
    }

    const auto versionFile = this->path / "version";
    std::uint8_t oldVersion{0}; // should use same type as this->version
    if (fs::exists(versionFile)) {
      std::ifstream iVersionFh{versionFile.string()};
      iVersionFh >> oldVersion;
      iVersionFh.close();
    }

    if (this->version > oldVersion) {
      std::ofstream oVersionFh{versionFile.string()};
      oVersionFh << this->version;
      oVersionFh.close();
    }

    // Create main .gitignore file.
    const auto gitignoreFile = this->path / ".gitignore";
    if (!fs::exists(gitignoreFile)) {
      std::ofstream gitignoreFh{gitignoreFile.string()};
      gitignoreFh << "/tmp/" << '\n';
      gitignoreFh << "/html/" << '\n';
      gitignoreFh.close();
    }

    // Remove old tmp/.gitignore file.
    const auto oldGitignoreFile = this->tmpPath / ".gitignore";
    if (fs::exists(oldGitignoreFile)) {
      fs::remove(oldGitignoreFile);
    }
  }

  void MutableWallet::createLock()
  {
    DLog(" -> MutableWallet::createLock()\n");

    // Already locked.
    if (this->isLocked) {
      return;
    }

    if (fs::exists(this->lockPath)) {
      throw std::string{"Wallet is locked."};
    }

    // Make tmp/ directory.
    if (!fs::exists(this->tmpPath)) {
      fs::create_directories(this->tmpPath);
    }

    // Create lock file.
    std::ofstream lockFh{this->lockPath.string()};
    lockFh << "locked\n";
    lockFh.close();

    this->isLocked = true;
  }

  void MutableWallet::removeLock() noexcept
  {
    DLog(" -> MutableWallet::removeLock()\n");

    if (!this->isLocked) {
      return;
    }

    // Remove lock file.
    const auto _lockPath = this->lockPath.string();
    if (fs::exists(_lockPath)) {
#ifdef __linux__
      std::remove(_lockPath.c_str());
#else
      fs::remove(_lockPath);
#endif
    }

    this->isLocked = false;
  }

  void MutableWallet::loadIndex() noexcept
  {
    DLog(" -> MutableWallet::loadIndex()\n");

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

    const auto idx = this->index["index"];
    if (!idx || !idx.IsDefined()) {
      this->isIndexModified = true;

      // Create new 'index' sequence.
      YAML::Node _idx{YAML::NodeType::Sequence};
      //_idx.push_back("hello_world");
      this->index["index"] = _idx;
    }
  }

  /**
   * Save the index to file.
   */
  void MutableWallet::saveIndex() noexcept
  {
    DLog(" -> MutableWallet::saveIndex()\n");

    // Skip function when nothing has been changed.
    if (!this->isIndexModified) {
      return;
    }
    this->isIndexModified = false;

    std::ofstream fout{this->indexPath.string()};
    fout << this->index << '\n';
    fout.close();
  }

  /**
   * Check entry exists.
   */
  bool MutableWallet::entryExists(const Entry& entry) noexcept
  {
    DLog(" -> MutableWallet::entryExists()\n");

    this->loadIndex();

    const auto _begin = this->index["index"].begin();
    const auto _end = this->index["index"].end();

    const auto it = std::find_if(_begin, _end, [&entry](const auto& item) {
      return item.template as<std::string>() == entry.id;
    });

    return it != _end;
  }

  void MutableWallet::loadEpics() noexcept
  {
    DLog(" -> MutableWallet::loadEpics()\n");

    if (this->areEpicsLoaded) {
      return;
    }

    this->areEpicsLoaded = true;

    if (fs::exists(this->epicsPath)) {
      // Load YAML file.
      this->epics = YAML::LoadFile(this->epicsPath.string());

      DLog(" -> MutableWallet::loadEpics() -> yaml loaded: %lu\n", this->epics.size());
    } else {
      // Create new epics file.
      this->areEpicsModified = true;
    }

    const auto idx = this->epics["epics"];
    if (!idx || !idx.IsDefined()) {
      this->areEpicsModified = true;

      // Create new 'epics' sequence.
      YAML::Node _idx{YAML::NodeType::Sequence};
      this->epics["epics"] = _idx;
    }
  }

  void MutableWallet::saveEpics() noexcept
  {
    DLog(" -> MutableWallet::saveEpics()\n");

    // Skip function when nothing has been changed.
    if (!this->areEpicsModified) {
      return;
    }
    this->areEpicsModified = false;

    std::ofstream fout{this->epicsPath.string()};
    fout << this->epics << '\n';
    fout.close();

    DLog(" -> MutableWallet::saveEpics() END\n");
  }

  /**
   * Check Epic exists by Handle.
   */
  bool MutableWallet::epicExists(const std::string& handle) noexcept
  {
    DLog(" -> MutableWallet::epicExists('%s')\n", handle.c_str());

    this->loadEpics();

    const auto _begin = this->epics["epics"].begin();
    const auto _end = this->epics["epics"].end();

    const auto it = std::find_if(_begin, _end, [&handle](const auto& item) {
      return item["handle"].template as<std::string>() == handle;
    });

    DLog(" -> MutableWallet::epicExists() -> found: %c\n", it != _end ? 'Y' : 'N');
    return it != _end;
  }

  /**
   * Check Epic exists by Epic Object.
   */
  bool MutableWallet::epicExists(const Epic& epic) noexcept
  {
    DLog(" -> MutableWallet::epicExists(Epic)\n");

    return this->epicExists(epic.handle);
  }
} // Wallet Namespace

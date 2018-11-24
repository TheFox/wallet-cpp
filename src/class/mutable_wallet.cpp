
#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>
#include <iostream>

#include "mutable_wallet.hpp"
#include "entry.hpp"
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
      const auto version = month["meta"]["version"].as<int>();
      if (version == 1) {
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

  MutableWallet::EntryMap MutableWallet::getEntries() const
  {
#ifdef DEBUG
    printf(" -> MutableWallet::getEntries()\n");
#endif

    EntryMap map{};

    if (!fs::exists(this->dataPath)) {
      throw std::string{"Wallet does not exists."};
    }

    for (auto& directoryItem : fs::directory_iterator(this->dataPath)) {
      const auto& filePath = directoryItem.path();
      const auto& fileStr = filePath.string();

      if (filePath.filename().string().substr(0, 6) != "month_"
        || fileStr.substr(fileStr.size() - 4) != ".yml") {
        continue;
      }

#ifdef DEBUG
      std::cout << "   -> file: " << directoryItem.path()
                //<< " '" << filePath.filename().string().substr(0, 6) << "'"
                << std::endl;
#endif

      auto yaml = YAML::LoadFile(fileStr);
      for (const auto& day : yaml["days"]) {
        auto node = day.second;
        std::cout << "     -> day: '" << day.first << "'" << std::endl;

        auto& dayMap = map[day.first.as<std::string>()];

        for (const auto& entryNode : node){
          std::cout << "     -> entry: '" << entryNode["id"] << "'" << std::endl;

          // emplace_back() is Nice!!
          dayMap.emplace_back(entryNode);
        }
      }
    }

    return map;
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

    // Create main .gitignore file.
    const path gitignoreFile = this->path / ".gitignore";
    if (!exists(gitignoreFile)) {
      ofstream gitignoreFh;
      gitignoreFh.open(gitignoreFile.string(), ofstream::out);
      gitignoreFh << "/tmp/" << '\n';
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

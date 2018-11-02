
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
  MutableWallet::MutableWallet(const std::string path) : path(path)
  {
#ifdef DEBUG
    printf("MutableWallet::MutableWallet\n");
#endif
  }

  MutableWallet::~MutableWallet()
  {
#ifdef DEBUG
    printf("MutableWallet::~MutableWallet\n");
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
    //this->createLock(); // TODO
    this->setupDirectories(explicitInit);
  }

  bool MutableWallet::add(const Entry entry, const bool isUnique)
  {
    using std::cout;
    using std::endl;
    using std::string;
    using std::ofstream;
    using fs::path;
    using fs::exists;
    using YAML::Node;
    using YAML::NodeType;
    using YAML::LoadFile;

#ifdef DEBUG
    printf("MutableWallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    const bool entryExists = this->entryExist(entry);
    if (isUnique && entryExists) {
      return false;
    }

    this->isIndexModified = true;
    this->index["index"].push_back(entry.getId());

    // Month File
    const auto monthFile = entry.getFileName();
    const auto monthFilePath = this->dataPath / monthFile;
    auto& monthFilePathStr = monthFilePath.string();

    const auto now = Components::getNowStr();

    Node month;
    if (exists(monthFilePathStr)) {
#ifdef DEBUG
      printf(" -> load month file: %s\n", monthFilePathStr.c_str());
#endif

      month = LoadFile(monthFilePathStr);
      month["meta"]["updated_at"] = now;
    } else {
#ifdef DEBUG
      printf(" -> create month file: %s\n", monthFilePathStr.c_str());
#endif

      Node meta(NodeType::Map);
      meta["version"] = 1;
      meta["created_at"] = now;
      meta["updated_at"] = now;
      month["meta"] = meta;

      Node days(NodeType::Map);
      month["days"] = days;
    }

    // Create day sequence.
    const string dayStr = entry.getDate();
    if (!month["days"][dayStr]) {
#ifdef DEBUG
      printf(" -> create new day: %s\n", entry.getDate().c_str());
#endif
      Node day(NodeType::Sequence);
      month["days"][dayStr] = day;
    }

    // TODO: add entry

    // Save Month file.
    ofstream fout(monthFilePathStr);
    fout << month;

    return true;
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
    using fs::remove;
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

    // Create data/.gitignore file.
    //const path dataGitignoreFile = this->dataPath / ".gitignore";
    //if (!exists(gitignoreFile)) {
    //  ofstream gitignoreFh;
    //  gitignoreFh.open(dataGitignoreFile.string(), ofstream::out);
    //  gitignoreFh << "*.lock" << '\n';
    //  gitignoreFh.close();
    //}

    // Remove old tmp/.gitignore file.
    const path oldGitignoreFile = this->tmpPath / ".gitignore";
    if (exists(oldGitignoreFile)) {
      remove(oldGitignoreFile);
    }
  }

  void MutableWallet::createLock()
  {
#ifdef DEBUG
    printf("MutableWallet::createLock\n");
#endif

    using fs::exists;
    using std::ofstream;

    // Already locked.
    if (this->isLocked) {
      return;
    }

    if (exists(this->lockPath)) {
      throw std::string{"Wallet is locked."};
    }

    // Create lock file.
    ofstream lockFh(this->lockPath.string());
    lockFh << "locked";
    lockFh.close();

    this->isLocked = true;
  }

  void MutableWallet::removeLock()
  {
#ifdef DEBUG
    printf("MutableWallet::removeLock\n");
#endif

    using fs::exists;
    using fs::remove;

    if (!this->isLocked) {
      return;
    }

    // Remove lock file.
    const auto _lockPath = this->lockPath.string();
    if (exists(_lockPath)) {
      remove(_lockPath);
    }

    this->isLocked = false;
  }

  void MutableWallet::loadIndex() noexcept
  {
#ifdef DEBUG
    printf("MutableWallet::loadIndex\n");
#endif

    using std::ifstream;
    using fs::exists;

    if (this->isIndexLoaded) {
      return;
    }
    this->isIndexLoaded = true;

    if (exists(this->indexPath)) {
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

    //#ifdef DEBUG
    //    printf(" -> index type %d\n", this->index["index"].Type());
    //#endif
  }

  /**
   * Save the index to file.
   */
  void MutableWallet::saveIndex() noexcept
  {
#ifdef DEBUG
    printf("MutableWallet::saveIndex\n");
#endif

    using std::ofstream;

    if (!this->isIndexModified) {
      return;
    }
    this->isIndexModified = false;

    ofstream fout(this->indexPath.string());
    fout << this->index;
  }

  /**
   * Check entry exists.
   *
   * @param entry
   * @return
   */
  bool MutableWallet::entryExist(const Entry& entry) noexcept
  {
#ifdef DEBUG
    printf("MutableWallet::entryExist\n");
#endif

    using std::find_if;
    using std::begin;
    using std::end;
    using std::string;

    this->loadIndex();

    //#ifdef DEBUG
    //    printf(" -> index type %d\n", this->index["index"].Type());
    //#endif

    const string id = entry.getId();
    const auto _b = this->index["index"].begin();
    const auto _e = this->index["index"].end();

    auto it = find_if(_b, _e, [&](const auto& item) {
      return item.template as<string>() == id;
    });

    //#ifdef DEBUG
    //    printf(" -> index type %d %d %c\n", this->index["index"].Type(), it == _b, it != _e ? 'Y' : 'N');
    //#endif

    return it != _e;
  }
} // Wallet Namespace


#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>
#include <iostream>

#ifdef __has_include
#  if __has_include(<yaml-cpp/yaml.h>)
#    include <yaml-cpp/yaml.h>
#  else
#     error "Missing <yaml-cpp/yaml.h>"
#  endif
#endif // __has_include

#include "mutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  MutableWallet::MutableWallet(const std::string path) : path(path)
  {
    printf("MutableWallet::MutableWallet\n");
  }

  void MutableWallet::setup() noexcept
  {
    this->setup(false);
  }

  void MutableWallet::setup(const bool explicitInit) noexcept
  {
    this->setupVariables();
    this->setupDirectories(explicitInit);
  }

  bool MutableWallet::add(const Entry entry, const bool isUnique)
  {
#ifdef DEBUG
    printf("MutableWallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    const bool entryExists = this->entryExist(entry);
    if (isUnique&&entryExists)
      return false;

    return false;
  }

  // Private
  void MutableWallet::setupVariables() noexcept
  {
    this->dataPath = this->path / "data";
    this->indexPath = this->dataPath / "index.yml";
    this->tmpPath = this->path / "tmp";

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

    // Create .gitignore file.
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
      remove(oldGitignoreFile);
    }
  }

  void MutableWallet::loadIndex() noexcept
  {
    using std::ifstream;

    if (this->isIndexLoaded) {
      return;
    }
    this->isIndexLoaded = true;

    // Open file.
    YAML::Node index = YAML::LoadFile(this->indexPath.string());
  }

  void MutableWallet::saveIndex() noexcept
  {
    if (!this->isIndexModified)
      return;
    this->isIndexModified = false;

    // TODO
  }

  bool MutableWallet::entryExist(const Entry& entry) noexcept
  {
    this->loadIndex();

    // TODO
    return false;
  }
} // Wallet Namespace

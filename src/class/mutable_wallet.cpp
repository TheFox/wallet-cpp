
#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>
#include <iostream>

#include "mutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  MutableWallet::MutableWallet(const std::string path) : path(path)
  {
  }

  bool MutableWallet::add(const Entry entry)
  {
#ifdef DEBUG
    printf("MutableWallet::add(%p)\n", &entry);
#endif
    return this->add(entry, false);
  }

  bool MutableWallet::add(const Entry entry, const bool isUnique)
  {
#ifdef DEBUG
    printf("MutableWallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    return false;
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

  void MutableWallet::setupVariables() noexcept
  {
    this->dataPath = this->path / "data";
    this->tmpPath = this->path / "tmp";
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
    path gitignoreFile = this->path / ".gitignore";
    if (!exists(gitignoreFile)) {
      ofstream gitignoreFh;
      gitignoreFh.open(gitignoreFile.string(), ofstream::out);
      gitignoreFh << "/tmp/" << '\n';
      gitignoreFh.close();
    }

    // Remove old tmp/.gitignore file.
    path oldGitignoreFile = this->tmpPath / ".gitignore";
    if (exists(oldGitignoreFile)) {
      remove(oldGitignoreFile);
    }
  }
} // Wallet Namespace

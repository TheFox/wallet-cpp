
#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>

#include "mutable_wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  MutableWallet::MutableWallet() : path(WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("MutableWallet::MutableWallet(def '%s')\n", this->path.c_str());
#endif
    this->setup();
  }

  MutableWallet::MutableWallet(const std::string path) : path(path)
  {
#ifdef DEBUG
    printf("MutableWallet::MutableWallet(str '%s')\n", this->path.c_str());
#endif
    this->setup();
  }

  MutableWallet::MutableWallet(const std::optional<std::string> path) : path(
    path.has_value() ? *path : WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("MutableWallet::MutableWallet(opt '%s')\n", this->path.c_str());
#endif
    this->setup();
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
    this->setupVariables();
    this->setupDirectories();
  }

  void MutableWallet::setupVariables() noexcept
  {
    this->dataPath = this->path / "data";
    this->tmpPath = this->path / "tmp";
  }

  void MutableWallet::setupDirectories() noexcept
  {
    using std::ofstream;
    using fs::exists;
    using fs::remove;
    using fs::path;
    using fs::create_directories;

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

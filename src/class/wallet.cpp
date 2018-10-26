
#ifdef DEBUG
#include <cstdio>
#endif

#include <fstream>

#include "wallet.hpp"
#include "entry.hpp"

namespace Wallet
{
  Wallet::Wallet() : path(WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(def '%s')\n", this->path.c_str());
#endif
    this->setup();
  }

  Wallet::Wallet(const std::string path) : path(path)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(str '%s')\n", this->path.c_str());
#endif
    this->setup();
  }

  Wallet::Wallet(const std::optional<std::string> path) : path(path.has_value() ? *path : WALLET_DEFAULT_PATH)
  {
#ifdef DEBUG
    printf("Wallet::Wallet(opt '%s')\n", this->path.c_str());
#endif
    this->setup();
  }

  bool Wallet::add(const Entry entry) noexcept
  {
#ifdef DEBUG
    printf("Wallet::add(%p)\n", &entry);
#endif
    return this->add(entry, false);
  }

  bool Wallet::add(const Entry entry, const bool isUnique) noexcept
  {
#ifdef DEBUG
    printf("Wallet::add(%p, u=%c)\n", &entry, isUnique ? 'Y' : 'N');
#endif

    return false;
  }

  void Wallet::setup() noexcept
  {
    using std::ofstream;
    using fs::exists;
    using fs::remove;
    using fs::path;
    using fs::create_directories;

    this->dataPath = this->path / "data";
    this->tmpPath = this->path / "tmp";

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
}

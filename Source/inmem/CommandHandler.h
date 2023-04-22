#pragma once

#include <memory>

#include "CacheStorage.h"
#include "ListnerCallback.h"

namespace Inmem {

class CommandHandler : public ListnerCallback {
public:
  CommandHandler(std::shared_ptr<CacheStorage> storage);
  std::string receive(std::string &&str) override;

private:
  std::shared_ptr<CacheStorage> storage;
};

} // namespace Inmem

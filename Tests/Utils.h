#pragma once

#include <memory>

#include "CacheStorage.h"

inline Inmem::Settings get_default_storage_settings() {
  return Inmem::Settings{.storage_initial_size = 1000};
}

inline std::shared_ptr<Inmem::CacheStorage> get_default_storage() {
  return std::make_shared<Inmem::CacheStorage>(get_default_storage_settings());
}

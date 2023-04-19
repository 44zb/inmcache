#include "CacheStorage.h"

namespace Inmem {
CacheStorage::CacheStorage(const Settings &settings)
    : storage(settings.storage_initial_size) {}

bool CacheStorage::is_value_numeric(const std::string& value) const {
  for (char c : value) {
    if (!std::isdigit(c)) {
      return false;
    }
  }

  return true;
}

std::string CacheStorage::get(const std::string &key) const {
  std::string result;

  auto item_itr = storage.find(key);
  if (item_itr != storage.end()) {
    auto &item = (&*item_itr)->second;

    if (item.type == CacheItemType::Numeric) {
      result = std::to_string(std::get<int64_t>(item.value));
    } else {
      result = std::get<std::string>(item.value);
    }
  }

  return result;
}

void CacheStorage::set(const std::string& key, std::string &&item_value) {
  CacheItem item(std::move(item_value));

  if (is_value_numeric(std::get<std::string>(item.value))) {
    item.type = CacheItemType::Numeric;

    item.value = std::stoll(std::get<std::string>(std::move(item.value)));
  }

  update_value(key, item);
}

void CacheStorage::set(const std::string &key, int64_t value) {
  CacheItem item(value);
  update_value(key, item);
}

void CacheStorage::remove(const std::string &key) {
  storage.erase(key);
}

bool CacheStorage::exists(const std::string &key) const {
  return storage.contains(key);
}

int64_t CacheStorage::increament(const std::string &key) {
  return increament_by(key, 1);
}

int64_t CacheStorage::decriment(const std::string &key) {
  return increament_by(key, -1);
}

int64_t CacheStorage::increament_by(const std::string &key, int64_t value) {
  auto item = storage.find(key);

  if (item == storage.end()) {
    update_value(key, value);
    return value;
  }

  if (item->second.type != CacheItemType::Numeric) {
    update_value(item, key, value);
    return value;
  }

  int64_t &val = std::get<int64_t>(item->second.value);
  val = val + value;
  return val;
}

void CacheStorage::update_value(const std::string &key, CacheItem item) {
  auto itr = storage.find(key);
  update_value(itr, key, item);
}

void CacheStorage::update_value(StorageType::iterator itr,
                                const std::string &key,
                                CacheItem item) {
  if (itr != storage.end()) {
    itr->second = item;
    return;
  }

  storage.insert({key, item});
}

CacheItem::CacheItem(std::string &&val)
    : type(CacheItemType::String), value(std::move(val)) {}

CacheItem::CacheItem(int64_t val) : type(CacheItemType::Numeric), value(val) {}

CacheItem::CacheItem() : CacheItem(0) {}

} // namespace Inmem
#pragma once

#include <string>
#include <unordered_map>
#include <variant>

namespace Inmem {
enum class CacheItemType { Numeric = 0, String = 1 };

struct Settings {
  size_t storage_initial_size = 1000;
};

class CacheItem {
public:
  CacheItem(std::string &&val);
  CacheItem(int64_t val);
  CacheItem();

  CacheItemType type;

  std::variant<int64_t, std::string> value;
};

class CacheStorage {
  using StorageType = std::unordered_map<std::string, CacheItem>;

public:
  CacheStorage(const Settings &settings);
  std::string get(const std::string &key) const;

  void set(const std::string &key, std::string &&value);
  void set(const std::string &key, int64_t value);

  void remove(const std::string &key);
  bool exists(const std::string &key) const;

  int64_t increament(const std::string &key);
  int64_t decriment(const std::string &key);

private:
  int64_t increament_by(const std::string &key, int64_t value);
  bool is_value_numeric(const std::string &value) const;

  void update_value(const std::string &key, CacheItem item);
  void update_value(StorageType::iterator itr, const std::string &key,
                    CacheItem item);

  StorageType storage;
};
} // namespace Inmem

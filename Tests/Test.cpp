#include <gtest/gtest.h>

#include "CacheStorage.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {
Inmem::Settings get_default_storage_settings() {
  return Inmem::Settings{.storage_initial_size = 1000};
}

Inmem::CacheStorage get_default_storage() {
  return Inmem::CacheStorage(get_default_storage_settings());
}

} // namespace

TEST(CacheStorage, test_set_get) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.set(key, "val");
  ASSERT_EQ(storage.get(key), "val");

  storage.set(key, "val1");
  ASSERT_EQ(storage.get(key), "val1");
}

TEST(CacheStorage, test_increment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.increament(key);

  ASSERT_EQ(storage.get(key), "1");

  storage.increament(key);
  ASSERT_EQ(storage.get(key), "2");

  storage.increament(key);
  ASSERT_EQ(storage.get(key), "3");
}

TEST(CacheStorage, test_decriment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.decriment(key);

  ASSERT_EQ(storage.get(key), "-1");

  storage.decriment(key);
  ASSERT_EQ(storage.get(key), "-2");

  storage.decriment(key);
  ASSERT_EQ(storage.get(key), "-3");
}

TEST(CacheStorage, test_decrement_increment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.decriment(key);
  ASSERT_EQ(storage.get(key), "-1");

  storage.increament(key);
  ASSERT_EQ(storage.get(key), "0");

  storage.increament(key);
  ASSERT_EQ(storage.get(key), "1");

  storage.decriment(key);
  ASSERT_EQ(storage.get(key), "0");

  storage.decriment(key);
  ASSERT_EQ(storage.get(key), "-1");
}

TEST(CacheStorage, test_string_to_number_conversion) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.set(key, "123");

  // If "key" is not numeric value incrementing will reset the value to 1 with CacheItemType::Numeric
  storage.increament(key);
  ASSERT_EQ(storage.get(key), "124");
}

TEST(CacheStorage, test_remove) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage.set(key, "qwe");

  ASSERT_EQ(storage.get(key), "qwe");

  storage.remove(key);
  ASSERT_EQ(storage.get(key), "");
  EXPECT_FALSE(storage.exists(key));
}

TEST(CacheStorage, test_exists) {
  auto storage = get_default_storage();
  std::string key = "key";

  EXPECT_FALSE(storage.exists(key));

  storage.set(key, "qwe");
  EXPECT_TRUE(storage.exists(key));
}


#include <gtest/gtest.h>

#include "Utils.h"

TEST(CacheStorage, set_get) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->set(key, "val");
  ASSERT_EQ(storage->get(key), "val");

  storage->set(key, "val1");
  ASSERT_EQ(storage->get(key), "val1");
}

TEST(CacheStorage, increment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->increament(key);

  ASSERT_EQ(storage->get(key), "1");

  storage->increament(key);
  ASSERT_EQ(storage->get(key), "2");

  storage->increament(key);
  ASSERT_EQ(storage->get(key), "3");
}

TEST(CacheStorage, decriment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->decriment(key);

  ASSERT_EQ(storage->get(key), "-1");

  storage->decriment(key);
  ASSERT_EQ(storage->get(key), "-2");

  storage->decriment(key);
  ASSERT_EQ(storage->get(key), "-3");
}

TEST(CacheStorage, decrement_increment) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->decriment(key);
  ASSERT_EQ(storage->get(key), "-1");

  storage->increament(key);
  ASSERT_EQ(storage->get(key), "0");

  storage->increament(key);
  ASSERT_EQ(storage->get(key), "1");

  storage->decriment(key);
  ASSERT_EQ(storage->get(key), "0");

  storage->decriment(key);
  ASSERT_EQ(storage->get(key), "-1");
}

TEST(CacheStorage, string_to_number_conversion) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->set(key, "123");

  // If "key" is not numeric value incrementing will reset the value to 1 with
  // CacheItemType::Numeric
  storage->increament(key);
  ASSERT_EQ(storage->get(key), "124");
}

TEST(CacheStorage, remove) {
  auto storage = get_default_storage();
  std::string key = "key";

  storage->set(key, "qwe");

  ASSERT_EQ(storage->get(key), "qwe");

  storage->remove(key);
  ASSERT_EQ(storage->get(key), "");
  EXPECT_FALSE(storage->exists(key));
}

TEST(CacheStorage, exists) {
  auto storage = get_default_storage();
  std::string key = "key";

  EXPECT_FALSE(storage->exists(key));

  storage->set(key, "qwe");
  EXPECT_TRUE(storage->exists(key));
}

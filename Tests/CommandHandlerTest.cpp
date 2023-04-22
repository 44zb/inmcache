#include <gtest/gtest.h>

#include "Utils.h"

#include "CommandHandler.h"

TEST(CommandHandler, set_get_commands) {
  auto storage = get_default_storage();
  Inmem::CommandHandler commandHandler(storage);
  EXPECT_TRUE(commandHandler.receive("SET KEY1 123").starts_with("DON"));
  EXPECT_EQ(commandHandler.receive("GET KEY1"), "123");
}

TEST(CommandHandler, wrong_command) {
  auto storage = get_default_storage();
  Inmem::CommandHandler commandHandler(storage);

  EXPECT_TRUE(commandHandler.receive("QWE QWE").starts_with("INV"));
}

TEST(CommandHandler, set_get_value_with_spaces_and_newlines) {
  auto storage = get_default_storage();
  Inmem::CommandHandler commandHandler(storage);

  std::string data = "123 123\ncheck-check\n check";

  EXPECT_TRUE(commandHandler.receive("SET KEY1 " + data).starts_with("DON"));
  EXPECT_EQ(storage->get("KEY1"), data);
  EXPECT_EQ(commandHandler.receive("GET KEY1"), data);
}

TEST(CommandHandler, wrong_param_count) {
  auto storage = get_default_storage();
  Inmem::CommandHandler commandHandler(storage);

  EXPECT_TRUE(commandHandler.receive("SET ").starts_with("ERR"));

  EXPECT_TRUE(commandHandler.receive("SET").starts_with("ERR"));
  EXPECT_TRUE(commandHandler.receive("GET").starts_with("ERR"));
  EXPECT_TRUE(commandHandler.receive("INC").starts_with("ERR"));
  EXPECT_TRUE(commandHandler.receive("DEC").starts_with("ERR"));
  EXPECT_TRUE(commandHandler.receive("REM").starts_with("ERR"));
  EXPECT_TRUE(commandHandler.receive("EXS").starts_with("ERR"));

  EXPECT_TRUE(commandHandler.receive("SET KEY1").starts_with("ERR"));
}
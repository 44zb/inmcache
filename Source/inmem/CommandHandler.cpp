#include "CommandHandler.h"

#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"

#include <string>

namespace Inmem {

namespace Response {
static inline std::string invalid_str{"INV"};
static inline std::string error_str{"ERR"};
static inline std::string done_str{"DON"};
} // namespace Response
static std::vector<std::string> command_list = {"GET", "SET", "INC",
                                                "DEC", "REM", "EXS"};

enum Commands {
  command_id_get = 0,
  command_id_set = 1,
  command_id_increment = 2,
  command_id_decrement = 3,
  command_id_remote = 4,
  command_id_exists = 5
};

CommandHandler::CommandHandler(std::shared_ptr<CacheStorage> storage)
    : storage(storage) {}

std::string CommandHandler::receive(std::string &&cmd) {

  std::vector<std::string> words;
  boost::split(words, cmd, boost::is_any_of(" "), boost::token_compress_on);

  if (words.size() <= 0) {
    return Response::invalid_str;
  }

  std::string command_str = words[0];
  auto command =
      std::find(command_list.begin(), command_list.end(), command_str);

  if (command == command_list.end()) {
    return Response::invalid_str;
  }

  size_t command_id = command - command_list.begin();

  switch (command_id) {
  case command_id_get:
    if (words.size() == 2) {
      return storage->get(std::move(words[1]));
    }
    return Response::error_str;
  case command_id_set:
    if (words.size() == 3) {
      storage->set(std::move(words[1]), std::move(words[2]));
      return Response::done_str;
    }
    return Response::error_str;
  case command_id_increment:
    if (words.size() == 2) {
      return std::to_string(storage->increament(std::move(words[1])));
    }
    return Response::error_str;
  case command_id_decrement:
    if (words.size() == 2) {
      return std::to_string(storage->decriment(std::move(words[1])));
    }
    return Response::error_str;
  case command_id_remote:
    if (words.size() == 2) {
      storage->remove(std::move(words[1]));
      return Response::done_str;
    }
    return Response::error_str;
  case command_id_exists:
    if (words.size() == 2) {
      return storage->exists(std::move(words[1])) ? "true" : "false";
    }
    return Response::error_str;
  }

  return Response::invalid_str;
}

} // namespace Inmem

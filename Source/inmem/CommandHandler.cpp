#include "CommandHandler.h"

#include <sstream>
#include <string>

namespace Inmem {
namespace Response {
std::string get_invalid_reponse(std::string_view text = "Invalid request") {
  return std::string("INV:").append(text);
}

std::string get_error_reponse(std::string_view text = "Unexpected error") {
  return std::string("ERR:").append(text);
};

std::string get_done_reponse(std::string_view text = "") {
  return std::string("DON").append(text);
};

std::string error_not_all_arg_provided() {
  return get_error_reponse("Not all required parameters were provided.");
}

} // namespace Response
static std::vector<std::string> command_list = {"GET", "SET", "INC",
                                                "DEC", "REM", "EXS"};

enum class Commands : uint8_t {
  Get = 0,
  Set = 1,
  Increment = 2,
  Decrement = 3,
  Remove = 4,
  Exists = 5
};

inline std::string get_reset_of_string(std::istringstream &ss,
                                       const std::string &str) {
  // +1 for skipping space symbol
  return std::string(str.begin() + ss.tellg() + 1, str.end());
}

CommandHandler::CommandHandler(std::shared_ptr<CacheStorage> storage)
    : storage(storage) {}

std::string CommandHandler::receive(std::string &&str) {
  std::istringstream ss(str);

  std::string command;
  ss >> command;

  auto command_itr =
      std::find(command_list.begin(), command_list.end(), command);

  // Enum values in commands have same value as
  Commands command_id =
      static_cast<Commands>(command_itr - command_list.begin());

  switch (command_id) {
  case Commands::Get: {
    std::string value = get_reset_of_string(ss, str);
    if (value.empty()) {
      return Response::error_not_all_arg_provided();
    }

    return storage->get(value);
  }

  case Commands::Set: {
    std::string arg;
    ss >> arg;

    std::string arg2(get_reset_of_string(ss, str));
    if (arg.empty() || arg2.empty()) {
      return Response::error_not_all_arg_provided();
    }
    storage->set(arg, std::move(arg2));
    return Response::get_done_reponse();
  }

  case Commands::Increment: {
    std::string arg;
    ss >> arg;
    if (arg.empty()) {
      return Response::error_not_all_arg_provided();
    }
    return std::to_string(storage->increament(arg));
  }

  case Commands::Decrement: {
    std::string arg;
    ss >> arg;

    if (arg.empty()) {
      return Response::error_not_all_arg_provided();
    }

    return std::to_string(storage->decriment(arg));
  }

  case Commands::Remove: {
    std::string arg;
    ss >> arg;

    if (arg.empty()) {
      return Response::error_not_all_arg_provided();
    }
    storage->remove(arg);
    return Response::get_done_reponse();
  }

  case Commands::Exists: {
    std::string arg;
    ss >> arg;

    if (arg.empty()) {
      return Response::error_not_all_arg_provided();
    }

    return storage->exists(arg) ? "TRUE" : "FALSE";
  }
  }

  return Response::get_invalid_reponse();
}

} // namespace Inmem

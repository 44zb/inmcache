#include <iostream>
#include <thread>

#include "inmem/CacheStorage.h"
#include "inmem/CommandHandler.h"
#include "inmem/TCPListner.h"

int main(int argc, char **argv) {
  using namespace Inmem;

  TCPListener listner(55555, std::thread::hardware_concurrency());

  auto storage =
      std::make_shared<CacheStorage>(Settings{.storage_initial_size = 1000});

  std::shared_ptr<ListnerCallback> callback =
      std::make_shared<CommandHandler>(storage);
  listner.registry_callback(callback);

  try {
    listner.listen();
  } catch (const std::exception &exp) {
    std::cerr << exp.what() << std::endl;
    return -1;
  }

  return 0;
}

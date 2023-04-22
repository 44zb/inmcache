#include "TCPListner.h"

namespace Inmem {

TCPListener::TCPListener(int32_t port, int32_t threads)
    : port(port), context(threads), signals(context, SIGINT, SIGTERM),
      callback(nullptr) {
  // Stop listening after receive termination signal
  signals.async_wait([&](auto, auto) { context.stop(); });
}

void TCPListener::registry_callback(
    std::shared_ptr<ListnerCallback> new_callback) {
  callback = new_callback;
}

void TCPListener::listen() {
  co_spawn(context, proccess(), detached);
  context.run();
}

awaitable<void> TCPListener::proccess() {
  auto executor = co_await asio::this_coro::executor;
  tcp_acceptor acceptor(executor, {tcp::v4(), port});

  for (;;) {
    tcp::socket socket = co_await acceptor.async_accept();

    co_spawn(executor, proccess_request(std::move(socket)), detached);
  }
}

awaitable<void> TCPListener::proccess_request(tcp::socket socket) {

  if (!callback.get()) {
    co_await async_write(socket, asio::buffer("Callback is not defined"),
                         asio::use_awaitable);
    co_return;
  }

  for (;;) {
    asio::streambuf buffer;
    size_t n = co_await asio::async_read_until(socket, buffer, '\0',
                                               asio::use_awaitable);

    std::string received_data =
        std::string((std::istreambuf_iterator<char>(&buffer)),
                    std::istreambuf_iterator<char>());

    // removing /0 character
    received_data.pop_back();

    std::string response = callback->receive(std::move(received_data));
    response.append("\n");

    co_await async_write(socket,
                         asio::buffer(response.c_str(), response.size()),
                         asio::use_awaitable);
  }
}

} // namespace Inmem

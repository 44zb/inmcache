#pragma once
#include <memory>

#include "ListnerCallback.h"
#include "boost/asio.hpp"

namespace Inmem {
namespace asio = boost::asio;

using boost::asio::awaitable;
using boost::asio::detached;
using boost::asio::ip::tcp;

using boost::asio::awaitable;
using tcp_acceptor = asio::use_awaitable_t<>::as_default_on_t<tcp::acceptor>;

class TCPListener {
public:
  TCPListener(int32_t port, int32_t threads);
  void registry_callback(std::shared_ptr<ListnerCallback> new_callback);
  void listen();

private:
  awaitable<void> proccess();
  awaitable<void> proccess_request(tcp::socket socket);

  asio::ip::port_type port;
  asio::io_context context;

  boost::asio::signal_set signals;

  std::shared_ptr<ListnerCallback> callback;
};
} // namespace Inmem

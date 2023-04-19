#pragma once

#include <string>

namespace Inmem {
class ListnerCallback {
public:
  virtual std::string receive(std::string &&cmd) = 0;
  virtual ~ListnerCallback() = default;
};
} // namespace Inmem

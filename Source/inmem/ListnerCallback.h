#pragma once

#include <string>

namespace Inmem {
class ListnerCallback {
public:
  virtual std::string receive(std::string &&str) = 0;
  virtual ~ListnerCallback() = default;
};
} // namespace Inmem

#include "receiver.h"
namespace meteo {

Receiver::Receiver(Logger& logger) : driver(2000, 34, 32), logger(logger) {}

bool Receiver::init() { return driver.init(); }

bool Receiver::receive(ReceiverData& data) {
  uint8_t size = sizeof(ReceiverData);
  return driver.recv(reinterpret_cast<uint8_t*>(&data), &size) &&
         size == sizeof(ReceiverData);
}
}  // namespace meteo
#pragma once
#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>

#include <cstring>

#include "logger.h"

namespace meteo {
struct ReceiverData {
  float temperature;
  float humidity;
};

class Receiver {
 public:
  explicit Receiver(Logger& logger);
  bool init();
  bool receive(ReceiverData& data);

 private:
  RH_ASK driver;
  Logger& logger;
};

}  // namespace meteo
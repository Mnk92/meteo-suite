#pragma once
// clang-format off
#include "logger.h"
#include <ThreeWire.h>
#include <RtcDS1302.h>
// clang-format on

namespace meteo {
struct RtcClockDateTime {
  bool isValid;
  std::uint16_t year;
  std::uint8_t month;
  std::uint8_t day;
  std::uint8_t hour;
  std::uint8_t minute;
  std::uint8_t second;
};
class RtcClock {
 public:
  explicit RtcClock(Logger& logger);
  bool init();
  RtcClockDateTime read();

 private:
  Logger& logger;
  ThreeWire wire;
  RtcDS1302<ThreeWire> rtc;
};

}  // namespace meteo
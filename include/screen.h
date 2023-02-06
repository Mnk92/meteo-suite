#pragma once
// clang-format off
#include "logger.h"
#include "receiver.h"
#include "rtc_clock.h"
#include "thp_sensor.h"
#include "co2_sensor.h"

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
// clang-format on

namespace meteo {
class Screen {
 public:
  explicit Screen(Logger& logger);
  bool init();
  void update(RtcClockDateTime const& rtc, Co2Data const& co2,
              THPData const& thp, ReceiverData* const receiver = nullptr);

 private:
  Logger& logger;
  GxEPD2_BW<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display;
  RtcClockDateTime rtcData;
  Co2Data co2Data;
  THPData thpData;
  ReceiverData receiverData;
};
}  // namespace meteo
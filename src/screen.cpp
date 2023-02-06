#include "screen.h"

namespace meteo {
Screen::Screen(Logger& logger)
    : logger(logger),
      display(GxEPD2_290_T94(/*CS=*/15, /*DC=*/27, /*RST=*/26,
                             /*BUSY=*/25)),
      rtcData{},
      co2Data{},
      thpData{},
      receiverData{} {}

bool Screen::init() {
  display.init(9600);
  display.hibernate();
  return true;
}

void Screen::update(RtcClockDateTime const& rtc, Co2Data const& co2,
                    THPData const& thp, ReceiverData* const receiver) {
  logger.log(LogLevel::INFO,
             "%f (%d)|%f|%f|%d (%d)|(%d)%d/%02d/%02d %02d:%02d:%02d",
             thp.temperature, co2.temperature, thp.humidity, thp.pressure,
             co2.co2, co2.accuracy, rtc.isValid, rtc.year, rtc.month, rtc.day,
             rtc.hour, rtc.minute, rtc.second);
  if (receiver) {
    logger.log(LogLevel::INFO, "EXTERNAL: %f %f", receiver->temperature,
               receiver->humidity);
  }
  rtcData = rtc;
  co2Data = co2;
  thpData = thp;
  if (receiver) {
    receiverData = *receiver;
  }
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.drawRect(0, 0, 20, 20, GxEPD_BLACK);
  } while (display.nextPage());
}
}  // namespace meteo
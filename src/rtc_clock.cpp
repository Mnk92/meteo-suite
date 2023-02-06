#include "rtc_clock.h"
namespace meteo {
RtcClock::RtcClock(Logger& logger)
    : logger(logger), wire(33, 12, 32), rtc(wire) {}

bool RtcClock::init() {
  rtc.Begin();
  const RtcDateTime compiled(__DATE__, __TIME__);
  if (!rtc.IsDateTimeValid()) {
    logger.log(LogLevel::INFO, "RTC lost confidence in the DateTime!");
    rtc.SetDateTime(compiled);
  }
  if (rtc.GetIsWriteProtected()) {
    logger.log(LogLevel::INFO, "RTC was write protected, enabling writing now");
    rtc.SetIsWriteProtected(false);
  }

  if (!rtc.GetIsRunning()) {
    logger.log(LogLevel::INFO, "RTC was not actively running, starting now");
    rtc.SetIsRunning(true);
  }
  if (auto const now = rtc.GetDateTime(); now < compiled) {
    logger.log(LogLevel::INFO,
               "RTC is older than compile time!  (Updating DateTime)");
    rtc.SetDateTime(compiled);
  }
  return rtc.GetIsRunning();
}

RtcClockDateTime RtcClock::read() {
  auto const time = rtc.GetDateTime();
  return {time.IsValid(), time.Year(),   time.Month(), time.Day(),
          time.Hour(),    time.Minute(), time.Second()};
}
}  // namespace meteo
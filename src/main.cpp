#include "screen.h"

using namespace meteo;
Logger logger;
THPSensor thp(logger);
Co2Sensor co2(logger);
RtcClock rtcClock(logger);
Receiver receiver(logger);
Screen screen(logger);
constexpr const char* boolToString(bool value) {
  return value ? "OK" : "FAILED";
}

void setup() {
  logger.init(LogLevel::INFO);
  logger.log(LogLevel::INFO, "Init bme280 %s", boolToString(thp.init()));
  logger.log(LogLevel::INFO, "Init co2 %s", boolToString(co2.init()));
  logger.log(LogLevel::INFO, "Init clock %s", boolToString(rtcClock.init()));
  logger.log(LogLevel::INFO, "Init receiver %s", boolToString(receiver.init()));
  logger.log(LogLevel::INFO, "Init screen %s", boolToString(screen.init()));
}

void loop() {
  auto const thpData = thp.read();
  auto const co2Data = co2.read();
  auto const rtcClockData = rtcClock.read();
  ReceiverData* receiverDataPtr{nullptr};
  if (static ReceiverData receiverData{}; receiver.receive(receiverData)) {
    receiverDataPtr = &receiverData;
  }
  screen.update(rtcClockData, co2Data, thpData, receiverDataPtr);
  delay(8000);
}
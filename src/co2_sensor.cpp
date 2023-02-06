#include "co2_sensor.h"
namespace meteo {
Co2Sensor::Co2Sensor(Logger& logger) : logger(logger), mhz(&Serial2) {}
bool Co2Sensor::init() {
  Serial2.begin(9600);
  return true;
}
Co2Data Co2Sensor::read() {
  if (auto response = mhz.retrieveData(); response == MHZ19_RESULT_OK) {
    return Co2Data{mhz.getTemperature(), mhz.getCO2(), mhz.getAccuracy()};
  } else {
    logger.log(LogLevel::ERROR, "Error, code: %d", response);
  }
  return Co2Data{-1, -1, -1};
}
}  // namespace meteo
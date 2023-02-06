#include "thp_sensor.h"

namespace meteo {
THPSensor::THPSensor(Logger& logger) : logger(logger) {}
bool THPSensor::init() {
  unsigned status;
  while (!(status = bme.begin(0x76))) {
    logger.log(LogLevel::ERROR,
               "Could not find a valid BME280 sensor, check wiring or try a "
               "different address!");
    logger.log(LogLevel::ERROR, "SensorID was: %08X", bme.sensorID());
    return false;
  }
  return true;
}

THPData THPSensor::read() {
  return {bme.readTemperature(), bme.readHumidity(), bme.readPressure() / 100};
}
}  // namespace meteo

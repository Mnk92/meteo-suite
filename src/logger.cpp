#include "logger.h"
namespace meteo {

void Logger::init(LogLevel level) {
  max_level = level;
  if (level != LogLevel::OFF) {
    Serial.begin(9600);
  }
}
}  // namespace meteo
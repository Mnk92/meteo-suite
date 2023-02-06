#pragma once
#include <Arduino.h>

namespace meteo {
enum class LogLevel : std::uint8_t {
  OFF = 0,
  ERROR = 1,
  WARNING = 2,
  INFO = 3,
  DEBUG = 4
};

class Logger {
 public:
  void init(LogLevel level);

  template <typename... Args>
  void log(LogLevel level, char const* message, Args&&... args) {
    if (level <= max_level) {
      Serial.print(levelToString(level));
      Serial.print(" | ");
      Serial.printf(message, args...);
      Serial.println();
    }
  }

 private:
  LogLevel max_level;

  const char* levelToString(LogLevel level) {
    switch (level) {
      case LogLevel::ERROR:
        return "Error";
      case LogLevel::WARNING:
        return "Warning";
      case LogLevel::INFO:
        return "Info";
      case LogLevel::DEBUG:
        return "Debug";
    };
    return "(unknown)";
  }
};
}  // namespace meteo
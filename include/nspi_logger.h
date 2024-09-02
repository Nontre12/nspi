#ifndef NSPI_LOGGER_H_
#define NSPI_LOGGER_H_

// std
#include <string>
#include <vector>

namespace nspi {

enum LogLevel { DEBUG = 0, INFO, ERROR };

class Logger {
 private:
  static const LogLevel level;
  static std::vector<std::string> logContent;

  static void log(const LogLevel&, const std::string&);

 public:
  Logger() = delete;
  ~Logger() = default;

  static void debug(const std::string&);
  static void info(const std::string&);
  static void error(const std::string&);

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  static const std::vector<std::string>& getLog() { return logContent; }
};

}  // namespace nspi

#endif  // NSPI_LOGGER_H_
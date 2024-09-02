#include "nspi_logger.h"

const nspi::LogLevel nspi::Logger::level = nspi::LogLevel::DEBUG;
std::vector<std::string> nspi::Logger::logContent;

void nspi::Logger::log(const LogLevel& level, const std::string& content) {
  if (level >= Logger::level) {
    Logger::logContent.push_back(content);
  }
}

void nspi::Logger::debug(const std::string& content) {
  Logger::log(LogLevel::DEBUG, "[DEBUG] " + content);
}

void nspi::Logger::info(const std::string& content) {
  Logger::log(LogLevel::INFO, "[INFO] " + content);
}

void nspi::Logger::error(const std::string& content) {
  Logger::log(LogLevel::ERROR, "[ERROR] " + content);
}

#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Custom exceptions for different error scenarios.
 */
class ShowNotFoundException : public std::runtime_error {
public:
  explicit ShowNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class SeatNotFoundException : public std::runtime_error {
public:
  explicit SeatNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class SeatNotAvailableException : public std::runtime_error {
public:
  explicit SeatNotAvailableException(const std::string& msg) : std::runtime_error(msg) {}
};
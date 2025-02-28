/**
 * @file ILoggable.h
 * @brief Abstract class to manage logging
 */

#pragma once
#include <string>

#include "LogUtility.h"  // This is not necessary but include here for convenience

/**
 * @class ILoggable
 * @brief Abstract class to manage logging
 * @note We wan to make this as an interface class, but to handle enable flag, we made this as abstract class
 */
class ILoggable {
 public:
  /**
   * @fn GetLogHeader
   * @brief Get headers to write in CSV output file
   * @return The headers
   */
  virtual std::string GetLogHeader() const = 0;

  /**
   * @fn GetLogValue
   * @brief Get values to write in CSV output file
   * @return The output values
   */
  virtual std::string GetLogValue() const = 0;

  bool IsLogEnabled = true;  //!< Log enable flag
};

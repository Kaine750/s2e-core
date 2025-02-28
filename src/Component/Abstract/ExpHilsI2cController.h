/**
 * @file ExpHilsI2cController.h
 * @brief Example of component emulation for I2C controller side communication in HILS environment
 */
#pragma once
#include <vector>

#include "ComponentBase.h"
#include "I2cControllerCommunicationBase.h"

/**
 * @class ExpHilsI2cController
 * @brief Example of component emulation for I2C controller side communication in HILS environment
 * @details Supposed to be used in connection with the following I2C-USB Controller converter
 *          SC18IM700 Data Sheet: https://www.nxp.com/docs/en/data-sheet/SC18IM700.pdf
 *          telemetry size = 5 bytes(ASCII)
 */
class ExpHilsI2cController : public ComponentBase, public I2cControllerCommunicationBase {
 public:
  /**
   * @fn ExpHilsI2cController
   * @brief Constructor
   * @param [in] prescaler: Frequency scale factor for update
   * @param [in] clock_gen: Clock generator
   * @param [in] hils_port_id: ID of HILS communication port
   * @param [in] baud_rate: Baud rate of HILS communication port
   * @param [in] tx_buf_size: TX (Controller to Target) buffer size
   * @param [in] rx_buf_size: RX (Target to Controller) buffer size
   * @param [in] hils_port_manager: HILS port manager
   */
  ExpHilsI2cController(const int prescaler, ClockGenerator* clock_gen, const unsigned int hils_port_id, const unsigned int baud_rate,
                       const unsigned int tx_buf_size, const unsigned int rx_buf_size, HilsPortManager* hils_port_manager);
  /**
   * @fn ~ExpHilsI2cController
   * @brief Destructor
   */
  ~ExpHilsI2cController();

 protected:
  // Override functions for ComponentBase
  /**
   * @fn MainRoutine
   * @brief Main routine to receive command and send telemetry
   */
  void MainRoutine(int count);

 private:
  /**
   * @fn RequestTlm
   * @brief Send command to the I2C-USB converter to send telemetry request command to the I2C Target
   */
  void RequestTlm();
  /**
   * @fn Receive
   * @brief Send command to the I2C-USB converter to read received data
   */
  void Receive();

  static const uint8_t kCmdHeader_ = 0x53;  //!< 'S' Header for SC18IM700
  static const uint8_t kReadCmd_ = 0x45;    //!< Read command for SC18IM700
  static const uint8_t kWriteCmd_ = 0x44;   //!< Write command for SC18IM700
  static const uint8_t kCmdFooter_ = 0x50;  //!< 'P' Footer for SC18IM700
};

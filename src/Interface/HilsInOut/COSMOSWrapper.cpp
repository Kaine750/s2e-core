/**
 * @file COSMOSWrapper.cpp
 * @brief Wrapper for COSMOS
 * @details COSMOS (Currently, called OpenC3) : https://openc3.com/
 * @note This file is very old and recently not managed well...
 */

#include "COSMOSWrapper.h"

COSMOSWrapper::COSMOSWrapper(bool enable) : enable_(enable) {
  // cosmos_tcp_if_ = new COSMOS_TCP_IF();
}

COSMOSWrapper::COSMOSWrapper() : enable_(false) {}

COSMOSWrapper::COSMOSWrapper(unsigned short port_num, bool enable, char* server_ip) : COSMOS_TCP_IF(port_num, server_ip), enable_(enable) {}

COSMOSWrapper::~COSMOSWrapper() {}

void COSMOSWrapper::Initialize() {
  if (!enable_) return;

  // Error messages are generated inside the Initialize function
  int ret = COSMOS_TCP_IF::Initialize();
}

void COSMOSWrapper::Finalize() { COSMOS_TCP_IF::Finalize(); }

bool COSMOSWrapper::Enable() const { return enable_; }

// Wrapper of cmd function to send data from COSMOS to RDP
void COSMOSWrapper::Cmd(std::string cmd_str) {
  if (!enable_) return;

  std::string expr = "cmd(\"";
  expr += cmd_str;
  expr += "\")";
  CosmosEval(expr);
}

void COSMOSWrapper::CosmosEval(std::string expr) {
  if (!enable_) return;
  // Expected the Ruby side directly pass the string to eval function
  COSMOS_TCP_IF::SendString(expr);
}

void COSMOSWrapper::Cmd_RDP_SAT_CMD_EXTERNAL_TORQUE(uint8_t torque_frame, uint32_t duration_ms, float ext_torque_x, float ext_torque_y,
                                                    float ext_torque_z) {
  if (!enable_) return;

  // cmd("SAT SAT_CMD_EXTERNAL_TORQUE with SYNC_HI 3162369199, SYNC_LO
  // 3737844679, LEN 21, AP_ID 2, OP_CODE 1, TORQUE_FRAME 'BODY', SPARE 0,
  // DURATION_MS 1000, EXT_TORQUE_X 0.1, EXT_TORQUE_Y 0, EXT_TORQUE_Z 0")
  // std::string cmd_str = "SAT SAT_CMD_EXTERNAL_TORQUE with TORQUE_FRAME ";
  std::string cmd_str =
      "SAT SAT_CMD_EXTERNAL_TORQUE with SYNC_HI 3162369199, SYNC_LO "
      "3737844679, LEN 21, AP_ID 2, OP_CODE 1, TORQUE_FRAME 'BODY', SPARE 0";

  // cmd_str += std::to_string(torque_frame);
  cmd_str += ", DURATION_MS ";
  cmd_str += std::to_string(duration_ms);
  cmd_str += ", EXT_TORQUE_X ";
  cmd_str += std::to_string(ext_torque_x);
  cmd_str += ", EXT_TORQUE_Y ";
  cmd_str += std::to_string(ext_torque_y);
  cmd_str += ", EXT_TORQUE_Z ";
  cmd_str += std::to_string(ext_torque_z);

  Cmd(cmd_str);
}

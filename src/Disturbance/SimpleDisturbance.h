/**
 * @file SimpleDisturbance.h
 * @brief Abstract class for a disturbance
 * @note It is better to use this abstract class for all disturbances, but it is difficult. (e.g. Gravity between spacecraft.)
 * In the difficult case, users need to use the Disturbance class directory.
 */

#pragma once
#include "../Dynamics/Dynamics.h"
#include "../Environment/Local/LocalEnvironment.h"
#include "Disturbance.h"

/**
 * @class SimpleDisturbance
 * @brief Abstract class for a disturbance
 */
class SimpleDisturbance : public Disturbance, public ILoggable {
 public:
  /**
   * @fn ~SimpleDisturbance
   * @brief Destructor
   */
  virtual ~SimpleDisturbance() {}

  /**
   * @fn UpdateIfEnabled
   * @brief Update calculated disturbance when the calculation flag is true
   */
  virtual inline void UpdateIfEnabled(const LocalEnvironment& local_env, const Dynamics& dynamics) {
    if (IsCalcEnabled) {
      Update(local_env, dynamics);
    } else {
      force_b_ *= 0;
      torque_b_ *= 0;
    }
  }

  /**
   * @fn Update
   * @brief Pure virtual function to define the disturbance calculation
   */
  virtual void Update(const LocalEnvironment& local_env, const Dynamics& dynamics) = 0;
};

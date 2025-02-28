/**
 * @file AttitudeRK4.h
 * @brief Class to calculate spacecraft attitude with Runge-Kutta method
 */
#ifndef __attitude_rk4_H__
#define __attitude_rk4_H__

#include "Attitude.h"

/**
 * @class AttitudeRK4
 * @brief Class to calculate spacecraft attitude with Runge-Kutta method
 */
class AttitudeRK4 : public Attitude {
 public:
  /**
   * @fn AttitudeRK4
   * @brief Constructor
   * @param [in] omega_b_ini: Initial value of spacecraft angular velocity of the body fixed frame [rad/s]
   * @param [in] quaternion_i2b_ini: Initial value of attitude quaternion from the inertial frame to the body fixed frame
   * @param [in] InertiaTensor_ini: Initial value of inertia tensor of the spacecraft [kg m^2]
   * @param [in] torque_b_ini: Initial torque acting on the spacecraft in the body fixed frame [Nm]
   * @param [in] prop_step_ini: Initial value of propagation step width [sec]
   * @param [in] sim_object_name: Simulation object name for Monte-Carlo simulation
   */
  AttitudeRK4(const Vector<3>& omega_b_ini, const Quaternion& quaternion_i2b_ini, const Matrix<3, 3>& InertiaTensor_ini,
              const Vector<3>& torque_b_ini, const double prop_step_ini, const std::string& sim_object_name = "Attitude");
  /**
   * @fn ~AttitudeRK4
   * @brief Destructor
   */
  ~AttitudeRK4();

  /**
   * @fn GetPropTime
   * @brief Return propagation time (current time) [sec]
   */
  inline double GetPropTime() const { return prop_time_s_; }

  /**
   * @fn SetTime
   * @brief Set propagation time (current time) [sec]
   */
  inline void SetTime(double set) { prop_time_s_ = set; }

  /**
   * @fn Propagate
   * @brief Attitude propagation
   * @param [in] endtime_s: Propagation endtime [sec]
   */
  virtual void Propagate(const double endtime_s);

  /**
   * @fn SetParameters
   * @brief Set parameters for Monte-Carlo simulation
   * @param [in] mc_sim: Monte-Carlo simulation executor
   */
  virtual void SetParameters(const MCSimExecutor& mc_sim);

 private:
  double prop_time_s_;  //!< current time [sec]

  /**
   * @fn Omega4Kinematics
   * @brief Generate angular velocity matrix for kinematics calculation
   * @param [in] omega: Angular velocity [rad/s]
   */
  Matrix<4, 4> Omega4Kinematics(Vector<3> omega);
  /**
   * @fn DynamicsKinematics
   * @brief Dynamics equation with kinematics
   * @param [in] x: State vector (angular velocity and quaternion)
   * @param [in] t: Unused TODO: remove?
   */
  Vector<7> DynamicsKinematics(Vector<7> x, double t);
  /**
   * @fn RungeOneStep
   * @brief Equation for one step of Runge-Kutta method
   * @param [in] t: Unused TODO: remove?
   * @param [in] dt: Step width [sec]
   */
  void RungeOneStep(double t, double dt);
};

#endif  //__attitude_rk4_H__

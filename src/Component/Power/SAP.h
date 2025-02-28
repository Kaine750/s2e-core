﻿/*
 * @file SAP.h
 * @brief Component emulation of Solar Array Panel
 */
#pragma once

#include <Environment/Local/LocalCelestialInformation.h>
#include <Environment/Local/SRPEnvironment.h>
#include <Interface/LogOutput/ILoggable.h>

#include <Library/math/Vector.hpp>

#include "../Abstract/ComponentBase.h"

class SAP : public ComponentBase, public ILoggable {
 public:
  /**
   * @fn SAP
   * @brief Constructor with prescaler
   * @param [in] prescaler: Frequency scale factor for update
   * @param [in] clock_gen: Clock generator
   * @param [in] id: SAP ID
   * @param [in] number_of_series: Number of series connected solar cells
   * @param [in] number_of_parallel: Number of parallel connected solar cells
   * @param [in] cell_area: Area of a solar cell [m2]
   * @param [in] normal_vector: Normal vector of SAP on the body fixed frame
   * @param [in] cell_efficiency: Power generation efficiency of solar cell
   * @param [in] transmission_efficiency: Efficiency of transmission to PCU
   * @param [in] srp: Solar Radiation Pressure environment
   * @param [in] local_celes_info: Local celestial information
   * @param [in] compo_step_time: Component step time [sec]
   */
  SAP(const int prescaler, ClockGenerator* clock_gen, int id, int number_of_series, int number_of_parallel, double cell_area,
      libra::Vector<3> normal_vector, double cell_efficiency, double transmission_efficiency, const SRPEnvironment* srp,
      const LocalCelestialInformation* local_celes_info, double compo_step_time);
  /**
   * @fn SAP
   * @brief Constructor with prescaler
   * @param [in] prescaler: Frequency scale factor for update
   * @param [in] clock_gen: Clock generator
   * @param [in] id: SAP ID
   * @param [in] number_of_series: Number of series connected solar cells
   * @param [in] number_of_parallel: Number of parallel connected solar cells
   * @param [in] cell_area: Area of a solar cell [m2]
   * @param [in] normal_vector: Normal vector of SAP on the body fixed frame
   * @param [in] cell_efficiency: Power generation efficiency of solar cell
   * @param [in] transmission_efficiency: Efficiency of transmission to PCU
   * @param [in] srp: Solar Radiation Pressure environment
   * @param [in] compo_step_time: Component step time [sec]
   */
  SAP(const int prescaler, ClockGenerator* clock_gen, int id, int number_of_series, int number_of_parallel, double cell_area,
      libra::Vector<3> normal_vector, double cell_efficiency, double transmission_efficiency, const SRPEnvironment* srp, double compo_step_time);
  /**
   * @fn SAP
   * @brief Constructor without prescaler
   * @note prescaler is set as 10, compo_step_sec is set as
   * @param [in] clock_gen: Clock generator
   * @param [in] id: SAP ID
   * @param [in] number_of_series: Number of series connected solar cells
   * @param [in] number_of_parallel: Number of parallel connected solar cells
   * @param [in] cell_area: Area of a solar cell [m2]
   * @param [in] normal_vector: Normal vector of SAP on the body fixed frame
   * @param [in] cell_efficiency: Power generation efficiency of solar cell
   * @param [in] transmission_efficiency: Efficiency of transmission to PCU
   * @param [in] srp: Solar Radiation Pressure environment
   * @param [in] local_celes_info: Local celestial information
   */
  SAP(ClockGenerator* clock_gen, int id, int number_of_series, int number_of_parallel, double cell_area, libra::Vector<3> normal_vector,
      double cell_efficiency, double transmission_efficiency, const SRPEnvironment* srp, const LocalCelestialInformation* local_celes_info);
  /**
   * @fn SAP
   * @brief Copy constructor
   */
  SAP(const SAP& obj);
  /**
   * @fn ~SAP
   * @brief Destructor
   */
  ~SAP();

  /**
   * @fn GetPowerGeneration
   * @brief Return power generation [W]
   */
  double GetPowerGeneration() const;
  /**
   * @fn SetVoltage
   * @brief Set voltage
   */
  void SetVoltage(const double voltage);

  // Override ILoggable
  /**
   * @fn GetLogHeader
   * @brief Override GetLogHeader function of ILoggable
   */
  std::string GetLogHeader() const override;
  /**
   * @fn GetLogValue
   * @brief Override GetLogValue function of ILoggable
   */
  std::string GetLogValue() const override;

 private:
  const int id_;                          //!< SAP ID TODO: Use string?
  const int number_of_series_;            //!< Number of series connected solar cells
  const int number_of_parallel_;          //!< Number of parallel connected solar cells
  const double cell_area_;                //!< Solar cell area [m^2]
  const libra::Vector<3> normal_vector_;  //!< Normal vector of SAP on the body fixed frame
  const double cell_efficiency_;          //!< Power generation efficiency of solar cell
  const double transmission_efficiency_;  //!< Efficiency of transmission to PCU

  const SRPEnvironment* const srp_;                    //!< Solar Radiation Pressure environment
  const LocalCelestialInformation* local_celes_info_;  //!< Local celestial information

  double voltage_;           //!< Voltage [V]
  double power_generation_;  //!< Generated power [W]

  static const double solar_constant_;  //!< Solar constant TODO: Use SRPEnvironment?
  static const double light_speed_;     //!< Speed of light TODO: Use PhysicalConstant?
  double compo_step_time_;              //!< Component step time [sec]

  // Override functions for ComponentBase
  /**
   * @fn MainRoutine
   * @brief Main routine to calculate force generation
   */
  void MainRoutine(int time_count) override;
};

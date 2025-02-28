/**
 * @file SensorBase.cpp
 * @brief Base class for sensor emulation to add noises
 */

#pragma once

#include <Library/math/GlobalRand.h>

template <size_t N>
SensorBase<N>::SensorBase(const libra::Matrix<N, N>& scale_factor, const libra::Vector<N>& range_to_const_c, const libra::Vector<N>& range_to_zero_c,
                          const libra::Vector<N>& bias_c, const libra::Vector<N>& nr_stddev_c, double rw_stepwidth,
                          const libra::Vector<N>& rw_stddev_c, const libra::Vector<N>& rw_limit_c)
    : scale_factor_(scale_factor),
      range_to_const_c_(range_to_const_c),
      range_to_zero_c_(range_to_zero_c),
      bias_c_(bias_c),
      n_rw_c_(rw_stepwidth, rw_stddev_c, rw_limit_c) {
  for (size_t i = 0; i < N; i++) {
    nrs_c_[i].set_param(0.0, nr_stddev_c[i], g_rand.MakeSeed());
  }
  RangeCheck();
}

template <size_t N>
SensorBase<N>::~SensorBase() {}

template <size_t N>
libra::Vector<N> SensorBase<N>::Measure(const libra::Vector<N> true_value_c) {
  libra::Vector<N> calc_value_c;
  calc_value_c = scale_factor_ * true_value_c;
  calc_value_c += bias_c_;
  for (size_t i = 0; i < N; ++i) {
    calc_value_c[i] += n_rw_c_[i];
    calc_value_c[i] += nrs_c_[i];
  }
  ++n_rw_c_;  // update Random Walk
  return Clip(calc_value_c);
}

template <size_t N>
libra::Vector<N> SensorBase<N>::Clip(const libra::Vector<N> input_c) {
  libra::Vector<N> output_c;
  for (size_t i = 0; i < N; ++i) {
    if (input_c[i] >= range_to_const_c_[i] && input_c[i] < range_to_zero_c_[i]) {
      output_c[i] = range_to_const_c_[i];
    } else if (input_c[i] <= -range_to_const_c_[i] && input_c[i] > -range_to_zero_c_[i]) {
      output_c[i] = -range_to_const_c_[i];
    } else if (fabs(input_c[i]) >= range_to_zero_c_[i]) {
      output_c[i] = 0.0;
    } else {
      output_c[i] = input_c[i];
    }
  }
  return output_c;
}

template <size_t N>
void SensorBase<N>::RangeCheck(void) {
  for (size_t i = 0; i < N; i++) {
    if (range_to_const_c_[i] < 0.0 || range_to_zero_c_[i] < 0.0) {
      std::cout << "SensorBase: Range should be positive!!\n";
      std::cout << "The range values are set as positive.\n";
      range_to_zero_c_[i] = fabs(range_to_zero_c_[i]);
      range_to_const_c_[i] = fabs(range_to_const_c_[i]);
    }
    if (range_to_const_c_[i] > range_to_zero_c_[i]) {
      std::cout << "SensorBase: range_zero should be greater than range_const!!\n";
      std::cout << "The range_zero is set as twice value of the range_const.\n";
      range_to_zero_c_[i] = 2.0 * range_to_const_c_[i];
    }
  }
}

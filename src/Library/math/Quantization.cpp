/**
 * @file Quantization.cpp
 * @brief Functions for quantization
 */

#include "Quantization.h"

double quantization(double continuous_num, double resolution) {
  int bin_num = (int)((double)continuous_num / resolution);
  return (double)bin_num * resolution;
}

float quantization_f(double continuous_num, double resolution) { return (float)quantization(continuous_num, resolution); }

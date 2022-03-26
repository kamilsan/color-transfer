#include "ColorLAlphaBeta.hpp"

#include <cmath>

#include "ColorLogLMS.hpp"

ColorLogLMS ColorLAlphaBeta::toLogLMS() const {
  const auto lScaled = std::sqrt(3.0f) / 3.0f * l;
  const auto alphaScaled = std::sqrt(6.0f) / 6.0f * alpha;
  const auto betaScaled = std::sqrt(2.0f) / 2.0f * beta; 

  const auto l = lScaled + alphaScaled + betaScaled;
  const auto m = lScaled + alphaScaled - betaScaled;
  const auto s = lScaled - 2.0f * alphaScaled;

  return ColorLogLMS{l, m, s};
}

ColorLAlphaBeta ColorLAlphaBeta::fromLogLMS(const ColorLogLMS& lms) {
  const auto l     = lms.l + lms.m + lms.s;
  const auto alpha = lms.l + lms.m - 2.0f * lms.s;
  const auto beta  = lms.l - lms.m;

  return ColorLAlphaBeta{l / std::sqrt(3.0f), alpha / std::sqrt(6.0f), beta / std::sqrt(2.0f)};
}
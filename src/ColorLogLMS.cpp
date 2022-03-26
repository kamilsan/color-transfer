#include "ColorLogLMS.hpp"

#include <cmath>

#include "ColorRGB.hpp"  

ColorRGB ColorLogLMS::toRGB() const {
  const auto lexp = std::exp(l - 0.00001f);
  const auto mexp = std::exp(m - 0.00001f);
  const auto sexp = std::exp(s - 0.00001f);

  const auto r =  4.4679f * lexp - 3.5873f * mexp + 0.1193f * sexp;
  const auto g = -1.2186f * lexp + 2.3809f * mexp - 0.1624f * sexp;
  const auto b =  0.0497f * lexp - 0.2439f * mexp + 1.2045f * sexp;

  return ColorRGB{r, g, b};
}

ColorLogLMS ColorLogLMS::fromRGB(const ColorRGB& rgb) {
  const auto l = 0.3811f * rgb.r + 0.5783f * rgb.g + 0.0402f * rgb.b;
  const auto m = 0.1967f * rgb.r + 0.7244f * rgb.g + 0.0784f * rgb.b;
  const auto s = 0.0241f * rgb.r + 0.1288f * rgb.g + 0.8444f * rgb.b;

  const auto logL = std::log(l + 0.00001f);
  const auto logM = std::log(m + 0.00001f);
  const auto logS = std::log(s + 0.00001f);

  return ColorLogLMS{logL, logM, logS};
}
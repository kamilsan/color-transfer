#include "ColorLMS.hpp"

#include "ColorRGB.hpp"  

ColorRGB ColorLMS::toRGB() const {
  const auto r =  4.4679f * l - 3.5873f * m + 0.1193f * s;
  const auto g = -1.2186f * l + 2.3809f * m - 0.1624f * s;
  const auto b =  0.0497f * l - 0.2439f * m + 1.2045f * s;

  return ColorRGB{r, g, b};
}

ColorLMS ColorLMS::fromRGB(const ColorRGB& rgb) {
  const auto l = 0.3811f * rgb.r + 0.5783f * rgb.g + 0.0402f * rgb.b;
  const auto m = 0.1967f * rgb.r + 0.7244f * rgb.g + 0.0784f * rgb.b;
  const auto s = 0.0241f * rgb.r + 0.1288f * rgb.g + 0.8444f * rgb.b;

  return ColorLMS{l, m, s};
}
#ifndef COLOR_RGB_HPP
#define COLOR_RGB_HPP

struct ColorRGB {
  ColorRGB(): r(0.0f), g(0.0f), b(0.0f) {}
  ColorRGB(float gray): r(gray), g(gray), b(gray) {}
  ColorRGB(float rr, float gg, float bb): r(rr), g(gg), b(bb) {}

  float r;
  float g;
  float b;
};

#endif // COLOR_RGB_HPP
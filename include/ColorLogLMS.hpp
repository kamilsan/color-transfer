#ifndef COLOR_LOG_LMS_HPP
#define COLOR_LOG_LMS_HPP

struct ColorRGB;

struct ColorLogLMS {
  ColorLogLMS(): l(0.0f), m(0.0f), s(0.0f) {}
  ColorLogLMS(float ll): l(ll), m(0), s(0) {}
  ColorLogLMS(float ll, float mm, float ss): l(ll), m(mm), s(ss) {}

  ColorRGB toRGB() const;
  static ColorLogLMS fromRGB(const ColorRGB& rgb);

  float l;
  float m;
  float s;
};

#endif // COLOR_LOG_LMS_HPP
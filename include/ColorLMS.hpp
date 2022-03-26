#ifndef COLOR_LMS_HPP
#define COLOR_LMS_HPP

struct ColorRGB;

struct ColorLMS {
  ColorLMS(): l(0.0f), m(0.0f), s(0.0f) {}
  ColorLMS(float ll): l(ll), m(0), s(0) {}
  ColorLMS(float ll, float mm, float ss): l(ll), m(mm), s(ss) {}

  ColorRGB toRGB() const;
  static ColorLMS fromRGB(const ColorRGB& rgb);

  float l;
  float m;
  float s;
};

#endif // COLOR_LMS_HPP
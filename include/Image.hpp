#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <memory>

#include "ColorRGB.hpp"

class Image {
public:
  Image(const std::string& filename);
  Image(unsigned int width, unsigned int height);

  Image(const Image& other);
  Image(Image&& other);

  bool save(const std::string& filename) const;
  ColorRGB getPixel(unsigned int x, unsigned int y) const;

  void setPixel(unsigned int x, unsigned int y, const ColorRGB& color);

  unsigned int getWidth() const { return width_; }
  unsigned int getHeight() const { return height_; }

  Image& operator=(const Image& other);
  Image& operator=(Image&& other);

  float operator[](int index) const { return pixels_[index]; }
  float& operator[](int index) { return pixels_[index]; }

private:
  float sRGBEncode(float c) const;
  float sRGBDecode(float c) const;

  unsigned int width_;
  unsigned int height_;
  std::unique_ptr<float[]> pixels_;
};


#endif // IMAGE_HPP
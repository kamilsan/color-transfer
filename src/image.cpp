#include "image.hpp"

#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(const std::string& filename) {
  int x, y, n;
  unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 0);

  width_ = x;
  height_ = y;
  
  const auto len = 3 * width_ * height_;
  pixels_ = std::make_unique<float[]>(len);

  for(unsigned int i = 0; i < len; ++i) {
    pixels_[i] = sRGBDecode(data[i] / 255.0f);
  }

  stbi_image_free(data);
}

Image::Image(unsigned int width, unsigned int height): width_(width), height_(height) {
  const auto len = 3 * width * height;
  pixels_ = std::make_unique<float[]>(len);
  std::memset(pixels_.get(), 0, len * sizeof(float));
}


Image::Image(const Image& other) {
  width_ = other.width_;
  height_ = other.height_;

  const auto len = 3 * width_ * height_;
  pixels_ = std::make_unique<float[]>(len);
  std::memcpy(pixels_.get(), other.pixels_.get(), len * sizeof(float));
}

Image::Image(Image&& other) {
  width_ = other.width_;
  height_ = other.height_;
  pixels_ = std::move(other.pixels_);
}

ColorRGB Image::getPixel(unsigned int x, unsigned int y) const {
  const auto baseIdx = 3 * (y * width_ + x);
  return ColorRGB{
    pixels_[baseIdx],
    pixels_[baseIdx + 1],
    pixels_[baseIdx + 2]
  };
}

void Image::setPixel(unsigned int x, unsigned int y, const ColorRGB& color) {
  const auto baseIdx = 3 * (y * width_ + x);
  pixels_[baseIdx] = color.r;
  pixels_[baseIdx + 1] = color.g;
  pixels_[baseIdx + 2] = color.b;
}

bool Image::save(const std::string& filename) const {
  const auto len = 3 * width_ * height_;
  auto data = std::make_unique<unsigned char[]>(len);

  for (unsigned int i = 0; i < len; ++i) {
    const float encoded = sRGBEncode(pixels_[i]);
    data[i] = std::min(255.0f, std::max(0.0f, 255.0f * encoded));
  }

  const auto stride = 3 * width_;
  const auto result = stbi_write_png(filename.c_str(), width_, height_, 3, data.get(), stride);
  return result != 0;
}

Image& Image::operator=(const Image& other) {
  if(&other != this) {
    width_ = other.width_;
    height_ = other.height_;

    const auto len = 3 * width_ * height_;
    pixels_ = std::make_unique<float[]>(len);
    std::memcpy(pixels_.get(), other.pixels_.get(), len * sizeof(float));
  }

  return *this;
}

Image& Image::operator=(Image&& other) {
  if(&other != this) {
    width_ = other.width_;
    height_ = other.height_;
    pixels_ = std::move(other.pixels_);
  }

  return *this;
}


float Image::sRGBEncode(float c) const {
  const float y = 1.0f / 2.4f;

  if (c <= 0.0031308f) {
    return c * 12.92f;
  }
  else {
    return 1.055f * std::pow(c, y) - 0.055f;
  }
}

float Image::sRGBDecode(float c) const {
  if (c <= 0.04045f) {
    return c / 12.92f;
  }
  else {
    return std::pow((c + 0.055f) / 1.055f, 2.4f);
  }
}
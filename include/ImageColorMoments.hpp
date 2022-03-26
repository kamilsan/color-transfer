#ifndef IMAGE_COLOR_MOMENTS_HPP
#define IMAGE_COLOR_MOMENTS_HPP

#include <array>
#include <cmath>

#include "ColorLAlphaBeta.hpp"
#include "ColorLogLMS.hpp"
#include "Image.hpp"

struct ImageMoments {
  float mean;
  float stDev;
};

std::array<ImageMoments, 3> getImageMoments(const Image& img) {
  float suml = 0.0f;
  float suma = 0.0f;
  float sumb = 0.0f;

  float sumlSq = 0.0f;
  float sumaSq = 0.0f;
  float sumbSq = 0.0f;

  std::array<ImageMoments, 3> moments;

  const auto oneOverN = 1.0f / (img.getWidth() * img.getHeight());

  for(unsigned int y = 0; y < img.getHeight(); ++y) {
    for(unsigned int x = 0; x < img.getWidth(); ++x) {
      const auto originalColor = img.getPixel(x, y);
      const auto colorLMS = ColorLogLMS::fromRGB(originalColor);
      const auto colorlab = ColorLAlphaBeta::fromLogLMS(colorLMS);

      suml += colorlab.l;
      suma += colorlab.alpha;
      sumb += colorlab.beta;

      sumlSq += colorlab.l * colorlab.l;
      sumaSq += colorlab.alpha * colorlab.alpha;
      sumbSq += colorlab.beta * colorlab.beta;
    }
  }

  moments[0].mean = suml * oneOverN;
  moments[0].stDev = std::sqrt(sumlSq * oneOverN - moments[0].mean * moments[0].mean);
  
  moments[1].mean = suma * oneOverN;
  moments[1].stDev = std::sqrt(sumaSq * oneOverN - moments[1].mean * moments[1].mean);
  
  moments[2].mean = sumb * oneOverN;
  moments[2].stDev = std::sqrt(sumbSq * oneOverN - moments[2].mean * moments[2].mean);

  return moments;
}

#endif // IMAGE_COLOR_MOMENTS_HPP
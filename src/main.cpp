#include <cmath>
#include <iostream>
#include <string>

#include "ColorLAlphaBeta.hpp"
#include "ColorLogLMS.hpp"
#include "Image.hpp"
#include "ImageColorMoments.hpp"

void printUsage(char* programName) {
  std::cout << "Usage:\n" << programName << " <image-to-transform> <image-style-source> <destination-image>\n\n";
  
  std::cout << "Where:\n";
  std::cout << "\t <image-to-transform> - path to source image to be colorized\n";
  std::cout << "\t <image-style-source> - path to image whose style will be transfered onto input image\n";
  std::cout << "\t <destination-image>  - path where output image can be saved\n\n";

  std::cout << "Example:\n";
  std::cout << "\t" << programName << " ./imgs/source_image.jpg ./imgs/source_style.jpg ./styled_image.png\n\n";
}

int main(int argc, char** argv)
{
  if(argc < 4) {
    printUsage(argv[0]);
    return 1;
  }

  const std::string sourceImagePath{argv[1]};
  const std::string styleImagePath{argv[2]};
  const std::string destinationImagePath{argv[3]};

  try {
    const Image img{sourceImagePath};
    const Image styleImg{styleImagePath};

    const auto sourceMoments = getImageMoments(img);
    const auto styleMoments = getImageMoments(styleImg);

    std::cout << "Source moments:\n";
    std::cout << "\tMean: (" << sourceMoments[0].mean << ", " << sourceMoments[1].mean << ", " << sourceMoments[2].mean << ")\n";
    std::cout << "\tStDev: (" << sourceMoments[0].stDev << ", " << sourceMoments[1].stDev << ", " << sourceMoments[2].stDev << ")\n";

    std::cout << "Style moments:\n";
    std::cout << "\tMean: (" << styleMoments[0].mean << ", " << styleMoments[1].mean << ", " << styleMoments[2].mean << ")\n";
    std::cout << "\tStDev: (" << styleMoments[0].stDev << ", " << styleMoments[1].stDev << ", " << styleMoments[2].stDev << ")\n";

    Image resultImage{img.getWidth(), img.getHeight()};

    const auto lScaleFactor = styleMoments[0].stDev / sourceMoments[0].stDev;
    const auto aScaleFactor = styleMoments[1].stDev / sourceMoments[1].stDev;
    const auto bScaleFactor = styleMoments[2].stDev / sourceMoments[2].stDev;

    for(unsigned int y = 0; y < img.getHeight(); ++y) {
      for(unsigned int x = 0; x < img.getWidth(); ++x) {
        const auto originalColor = img.getPixel(x, y);
        const auto colorLMS = ColorLogLMS::fromRGB(originalColor);
        const auto colorlab = ColorLAlphaBeta::fromLogLMS(colorLMS);

        const auto lCentered = colorlab.l - sourceMoments[0].mean;
        const auto aCentered = colorlab.alpha - sourceMoments[1].mean;
        const auto bCentered = colorlab.beta - sourceMoments[2].mean;

        const auto lScaled = lCentered * lScaleFactor;
        const auto aScaled = aCentered * aScaleFactor;
        const auto bScaled = bCentered * bScaleFactor;

        const auto lFinal = lScaled + styleMoments[0].mean;
        const auto aFinal = aScaled + styleMoments[1].mean;
        const auto bFinal = bScaled + styleMoments[2].mean;

        const auto styledColorRGB = ColorLAlphaBeta{lFinal, aFinal, bFinal}.toLogLMS().toRGB();
        const auto clampedRGB = ColorRGB{
          std::min(1.0f, std::max(0.0f, styledColorRGB.r)),
          std::min(1.0f, std::max(0.0f, styledColorRGB.g)),
          std::min(1.0f, std::max(0.0f, styledColorRGB.b))
        };

        resultImage.setPixel(x, y, clampedRGB);
      }
    }

    resultImage.save(destinationImagePath);
  }
  catch(std::exception& ex) {
    std::cout << "ERROR: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}
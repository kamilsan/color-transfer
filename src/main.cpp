#include <iostream>
#include <string>

#include "image.hpp"
#include "ColorLAlphaBeta.hpp"
#include "ColorLMS.hpp"

void printUsage(char* programName) {
  std::cout << "Usage:\n" << programName << " <image-to-transform> <image-style-source> <destination-image>\n\n";
  
  std::cout << "Where:\n";
  std::cout << "\t <image-to-transform> - path to source image to be colorized\n";
  std::cout << "\t <image-style-source> - path to image whose style will be transfered onto input image\n";
  std::cout << "\t <destination-image>  - path where output image can be saved\n\n";

  std::cout << "Example:\n";
  std::cout << "\t" << programName << " ./imgs/source_image.png ./imgs/source_style.png ./styled_image.png\n\n";
}

int main(int argc, char** argv)
{
  if(argc < 4) {
    printUsage(argv[0]);
    return 1;
  }

  const std::string sourceImagePath{argv[1]};
  // const std::string styleImagePath{argv[2]};
  const std::string destinationImagePath{argv[3]};

  Image img{sourceImagePath};

  for(unsigned int y = 0; y < img.getHeight(); ++y) {
    for(unsigned int x = 0; x < img.getWidth(); ++x) {
      const auto originalColor = img.getPixel(x, y);
      const auto colorLMS = ColorLMS::fromRGB(originalColor);
      const auto colorlab = ColorLAlphaBeta::fromLMS(colorLMS);

      const auto roundtripRGB = colorlab.toLMS().toRGB();
      img.setPixel(x, y, roundtripRGB);
    }
  }

  img.save(destinationImagePath);

  return 0;
}
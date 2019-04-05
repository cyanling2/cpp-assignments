#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using cs225::PNG;
using cs225::HSLAPixel;

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;
  PNG image1;
  image.readFromFile(inputFile);
  image1.readFromFile(inputFile);
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      HSLAPixel & pixel1 = image1.getPixel(image.width()-1-x,image.height()-1-y);
      pixel1.h=pixel.h;
      pixel1.s=pixel.s;
      pixel1.l=pixel.l;
      pixel1.a=pixel.a;
    }
  }
  image1.writeToFile(outputFile);
  return;



}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height/3; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h=11;
      pixel.s=1;
      pixel.l=0.5;
      pixel.a=1;
    }
  }
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = height/3; y < height/3*2; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h=216;
      pixel.s=1;
      pixel.l=0.5;
      pixel.a=1;
    }
  }
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = height/3*2; y < height; y++) {
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h=300;
      pixel.s=1;
      pixel.l=0.5;
      pixel.a=1;
    }
  }


  return png;
}

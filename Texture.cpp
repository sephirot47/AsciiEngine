#include "Texture.h"

using namespace ae;

Texture::Texture()
{
}

void Texture::loadFromFile(const std::string &filepath)
{
  unsigned char *cdata = FileReader::ReadImage(filepath.c_str(), this->components, this->width, this->height);

  //Store in data as 0..1 instead of 0..255
  data = std::vector<float>(height*width * components, 0.0f);
  for(int i = 0; i < width; ++i) //Convert from 0..255 to 0..1
  {
      for(int j = 0; j < height; ++j)
      {
         data[(j*width+i) * components    ] = float(cdata[(j*width+i) * components    ]) / 255;
         data[(j*width+i) * components + 1] = float(cdata[(j*width+i) * components + 1]) / 255;
         data[(j*width+i) * components + 2] = float(cdata[(j*width+i) * components + 2]) / 255;
         data[(j*width+i) * components + 3] = float(cdata[(j*width+i) * components + 3]) / 255;
      }
  }
}

#ifndef TEXTURE_AE_H
#define TEXTURE_AE_H

#include "FileReader.h"
#include "AsciiGL/AsciiGL.h"

namespace ae
{

class Texture : public agl::Texture
{
public:
    Texture();
    void loadFromFile(const std::string &filepath);
};

}

#endif // TEXTURE_AE_H

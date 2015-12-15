#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "AsciiGL/AsciiGL.h"
#include "stb_image.h"


namespace ae
{

class FileReader
{
private:
  static void GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles);

public:

  FileReader();

  static bool ReadOBJ(const char *filepath, std::vector<glm::vec3> &vertexPos,
                      std::vector<glm::vec2> &vertexUvs,
                      std::vector<glm::vec3> &vertexNormals,
                      bool &triangles);

  static unsigned char* ReadImage(const char *filepath, int &components, int &width, int &height);
};
}


#endif // FILEREADER_H

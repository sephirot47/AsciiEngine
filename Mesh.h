#ifndef MESH_H
#define MESH_H

#include <vector>
#include "FileReader.h"
#include "AsciiGL/AsciiGL.h"

namespace ae
{

class Mesh
{
private:

    float minx, miny, minz, maxx, maxy, maxz;

    std::vector<glm::vec3> pos, normals;
    std::vector<glm::vec2> uvs;

    agl::VAO vao;

public:

    Mesh();
    void loadFromFile(const std::string &file);

    agl::VAO *getVAO();
};

}

#endif // MESH_H

#include "Mesh.h"

using namespace ae;

Mesh::Mesh()
{
}

void Mesh::loadFromFile(const std::string &file)
{
    bool triangles;
    FileReader::ReadOBJ(file.c_str(), pos, uvs, normals, triangles);

    vao.addVBO("position", pos);
    vao.addVBO("normal", normals);
    vao.addVBO("uv", uvs);

    //Get bounding box /////////
    minx = miny = minz = 99999;
    maxx = maxy = maxz = -99999;
    for(int i = 0; i < pos.size(); ++i)
    {
      minx = std::min(minx, pos[i].x);
      maxx = std::max(maxx, pos[i].x);
      miny = std::min(miny, pos[i].y);
      maxy = std::max(maxy, pos[i].y);
      minz = std::min(minz, pos[i].z);
      maxz = std::max(maxz, pos[i].z);
    }
    ////////////////////////////
}

agl::VAO *Mesh::getVAO()
{
    return &vao;
}

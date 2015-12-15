#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "AsciiGL/AsciiGL.h"
#include "Component.h"

namespace ae
{

class Transform : public Component
{
public:

    Transform();

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    void getModelMatrix(glm::mat4 &modelMatrix) const;
};

}

#endif // TRANSFORM_H

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform : Component
{
public:

    Transform();

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    void getModelMatrix(glm::mat4 &modelMatrix) const;
};

#endif // TRANSFORM_H

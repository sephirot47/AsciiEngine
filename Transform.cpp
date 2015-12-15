#include "Transform.h"

Transform::Transform() :  position(glm::vec3(.0f)), rotation(glm::quat()), scale(glm::vec3(1.0f))
{

}

void Transform::getModelMatrix(glm::mat4 &modelMatrix) const
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::mat4_cast(rotation) * modelMatrix;
    modelMatrix = glm::translate(modelMatrix, position);
}

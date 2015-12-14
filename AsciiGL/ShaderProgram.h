#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "VAO.h"
#include "GenericMap.h"
#include <functional>


namespace agl 
{
class ShaderProgram
{
public:
    GenericMap uniforms;

    std::function<glm::vec4 (const GenericMap&, const GenericMap&, GenericMap&)> vertexShader;
    std::function<glm::vec4 (const GenericMap&, const GenericMap&)> fragmentShader;

    ShaderProgram();
};
}

#endif // SHADERPROGRAM_H

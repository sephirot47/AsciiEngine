#ifndef PIPELINE_H
#define PIPELINE_H

#define GLM_SWIZZLE

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
#include <thread>

#include "Framebuffer.h"
#include "ShaderProgram.h"


namespace agl 
{
class Pipeline
{
private:
    static inline bool vertexOutOfViewCube(const glm::vec4 &v);
    static inline void vertexToDeviceCoords(glm::vec4 &v, int w, int h);

    void  drawLine(const glm::vec3 &v0_3,
                   const glm::vec3 &v1_3,
                   const std::vector<GenericMap> &lineVertexAttributes,
                   Framebuffer &framebuffer) const;

    void  drawTriangle(const glm::vec3 &v0_3,
                       const glm::vec3 &v1_3,
                       const glm::vec3 &v2_3,
                       const std::vector<GenericMap> &triangleFragmentAttributes,
                       Framebuffer &framebuffer) const;

    static float edgeFunction(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c);

    glm::vec4 applyVertexShader(const GenericMap &vertexAttributes,
                                GenericMap &fragmentAttributes) const;

    glm::vec4 applyTriangleFragmentShader(const std::vector<GenericMap> &vertexAttributes, const glm::vec3 &ws,  const glm::vec3 fragmentPos) const;
    glm::vec4 applyLineFragmentShader(const std::vector<GenericMap> &vertexAttributes, float w,  const glm::vec3 fragmentPos) const;
    void drawVAOthread(VAO &vao, Framebuffer &framebuffer, int nThreads, int m) const;
public:

    ShaderProgram program;
    bool wireframe;

    Pipeline();

    void drawVAO(VAO &vao, Framebuffer &framebuffer) const;
};
}

#endif // PIPELINE_H

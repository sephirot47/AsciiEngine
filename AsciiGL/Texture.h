#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include "glm/glm.hpp"

namespace agl 
{
class Texture
{
protected:
  std::vector<float> data;
  int components, width, height;

public:
  Texture();
  Texture(int w, int h, int components, float initialValue = 0.0f);

  void loadFromMatrix(const std::vector< std::vector<float> > &dataMatrix);

  int getWidth() { return width; }
  int getHeight() { return height; }
  int getComponents() { return components; }

                           //component = 0,1,2,3...
  void set(int x, int y, int component, float value); //set a specific component
  void set(int x, int y, float value); //For 1 component
  void set(int x, int y, const glm::vec2& value); //For 2 components
  void set(int x, int y, const glm::vec3& value); //For 3 components
  void set(int x, int y, const glm::vec4& value); //For 4 components

  float sample(int x, int y, int component) const;
  glm::vec4 sample(float s, float r) const;
  glm::vec4 sample(int x, int y) const;
};
}

#endif // TEXTURE_H

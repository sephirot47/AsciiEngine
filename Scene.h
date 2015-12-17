#ifndef SCENE_H
#define SCENE_H

#include "Texture.h"
#include "Transform.h"
#include "Mesh.h"
#include "GameObject.h"
#include "AsciiGL/AsciiGL.h"

namespace ae
{

class Scene
{
friend class Game;

private:

  agl::Framebuffer framebuffer;
  agl::Pipeline pl;
  GameObject luigi;

public:

  Scene(int width, int height);
  void renderToFramebuffer();
};

}

#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H

#include "Texture.h"
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

public:

  Scene(int width, int height);
};

}

#endif // SCENE_H

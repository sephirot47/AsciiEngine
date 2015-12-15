#ifndef SCENE_H
#define SCENE_H

#include "AsciiGL/AsciiGL.h"

class Scene
{
private:

  agl::Framebuffer framebuffer;
  agl::Pipeline pl;

public:

  Scene();
  Scene(int width, int height);

  void display(agl::Window &window);
};

#endif // SCENE_H

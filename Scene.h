#ifndef SCENE_H
#define SCENE_H

#include <map>

#include "AsciiGL/AsciiGL.h"

#include "Texture.h"
#include "Transform.h"
#include "Mesh.h"
#include "GameObject.h"

namespace ae
{

class Scene
{
friend class Game;

private:

  agl::Pipeline pl;
  std::vector<GameObject> gameObjects;
  GameObject luigi;

public:

  Scene();
  void render(agl::Framebuffer &framebuffer);

  void addGameObject(GameObject &go);
  GameObject* getGameObject(const std::string &name);
};

}

#endif // SCENE_H

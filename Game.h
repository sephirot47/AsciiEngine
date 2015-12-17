#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "Window.h"

#include "Framebuffer.h"
#include "FileReader.h"
#include "Pipeline.h"
#include "Texture.h"
#include "Debug.h"
#include "VAO.h"

#include "GameObject.h"
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"

#include "Scene.h"
#include "AsciiGL/AsciiGL.h"

using namespace ae;

namespace ae
{

class Game
{
public:
  agl::Window window;
  Scene currentScene;

  Game();
  void loop();
};

}

#endif // GAME_H

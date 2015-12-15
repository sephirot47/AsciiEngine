#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define GLM_SWIZZLE
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

using namespace std;
using namespace agl;
using namespace ae;

class Game
{
private:
  void loop();

public:
  Scene scene;
  agl::Window window;
  agl::Pipeline pl;

  Game();
};

#endif // GAME_H

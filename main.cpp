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
#include "Game.h"
#include "Transform.h"

using namespace std;
using namespace agl;
using namespace ae;


int main()
{
  GameObject luigi;
  luigi.addComponent<Transform>();
  luigi.addComponent<Mesh>();
  luigi.getComponent<Mesh>()->loadFromFile("./luigi-lowpoly.obj");

  Game game;

  getch();
  endwin();
}

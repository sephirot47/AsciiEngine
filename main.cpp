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
#include "Game.h"
#include "Transform.h"

using namespace std;
using namespace agl;
using namespace ae;


int main()
{
  Game game;
  game.loop();
  getch();
  endwin();
}

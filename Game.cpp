#include "Game.h"

using namespace std;
using namespace agl;
using namespace ae;

Game::Game() : window(agl::Window(0, 0, agl::Window::getMaxWidth(), agl::Window::getMaxHeight())),
               currentScene(Scene(window.getWidth(), window.getHeight()))
{
    srand(time(0));
}

void Game::loop()
{
  while (true)
  {
    debugLog("Rand: " << rand());

    window.erase();

    //Render scene
    currentScene.renderToFramebuffer();
    window.render(currentScene.framebuffer);
    window.display();
    //

    Debug::showWindow();
  }
}

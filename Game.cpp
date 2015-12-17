#include "Game.h"

using namespace ae;

Game::Game() : window(agl::Window(0, 0, agl::Window::getMaxWidth(), agl::Window::getMaxHeight()))
{
    srand(time(0));
    framebuffer = agl::Framebuffer(window.getWidth(), window.getHeight());
}

void Game::loop()
{
  while (true)
  {
    debugLog("Rand: " << rand());

    framebuffer.clearBuffers();
    window.erase();

    //Render scene
    currentScene.render(framebuffer);
    window.render(framebuffer);
    window.display();
    //

    Debug::showWindow();
  }
}

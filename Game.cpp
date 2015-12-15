#include "Game.h"

using namespace std;
using namespace agl;
using namespace ae;

Game::Game() : window(agl::Window(0, 0, agl::Window::getMaxWidth(), agl::Window::getMaxHeight())),
               currentScene(Scene(window.getWidth(), window.getHeight()))
{
  ae::Texture *texture = new ae::Texture();
  texture->loadFromFile("luigiD.jpg");
  pl.program.uniforms.set("tex", texture);
}

void Game::loop()
{
  static float trans = 0.0f, rotation = 0.0f;
  static float cameraX = 0.0f, cameraZ = 0.0f;

  GameObject luigi;
  luigi.addComponent<Transform>();
  luigi.addComponent<Mesh>();
  luigi.getComponent<Mesh>()->loadFromFile("./luigi-lowpoly.obj");

  while (true)
  {
    window.erase();

    int ch = getch();
    if (ch == 'a')
    {
      debugLog("LEFT");
      cameraX += 0.5f;
    }
    else if (ch == 'd')
    {
      debugLog("RIGHT");
      cameraX -= 0.5f;
    }
    else if (ch == 'w')
    {
      debugLog("FORWARD");
      cameraZ += 0.5f;
    }
    else if (ch == 's')
    {
      debugLog("BACKWARDS");
      cameraZ -= 0.5f;
    }

    glm::mat4 V(1.0f);
    V = glm::lookAt(glm::vec3(cameraX,0,cameraZ),glm::vec3(cameraX,0,cameraZ-20),glm::vec3(0,1,0));
    pl.program.uniforms.set("V", V);

    trans += 0.05;
    rotation += 0.005f;

    glm::mat4 M(1.0f);

    Transform& t = *(luigi.getComponent<Transform>());
    t.position =  glm::vec3(-12, -8, ((sin(trans)*0.5+0.5f)*-37)-1);
    t.rotation = glm::angleAxis(rotation*5, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.15);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), currentScene.framebuffer);

    t.position =   glm::vec3(((sin(trans*0.5f))*3),-15,-20);
    t.rotation = glm::angleAxis( rotation*9, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), currentScene.framebuffer);

    t.position =  glm::vec3(12,-8,-13);
    t.rotation = glm::angleAxis(rotation*14, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), currentScene.framebuffer);

    //Render scene
    currentScene.framebuffer.clearBuffers();
    window.render(currentScene.framebuffer);
    window.display();
    //

    Debug::showWindow();
  }
}

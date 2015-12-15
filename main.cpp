#include <vector>
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "stb_image.h"

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

using namespace std;
using namespace agl;
using namespace ae;

glm::vec4 vshader(const GenericMap &vertexAttributes, const GenericMap &uniforms, GenericMap &fragmentAttributes)
{
  glm::mat4 M, P, V;
  uniforms.getMat4("M", M);
  uniforms.getMat4("P", P);
  uniforms.getMat4("V", V);

  glm::vec3 pos, normal;
  vertexAttributes.getVec3("position", pos);
  vertexAttributes.getVec3("normal", normal);

  glm::vec4 tPos, tNormal;
  tPos = (M * glm::vec4(pos, 1));
  tNormal = (M * glm::vec4(normal, 0));

  glm::vec2 uv; vertexAttributes.getVec2("uv", uv);
  fragmentAttributes.set("uv", uv);
  fragmentAttributes.set("normal", tNormal.xyz());
  fragmentAttributes.set("position", tPos.xyz());
  return P * V * tPos;
}

glm::vec4 fshader(const GenericMap &fragmentAttributes, const GenericMap &uniforms)
{
  glm::vec3 normal;
  fragmentAttributes.getVec3("normal", normal);
  normal = glm::normalize(normal);

  glm::vec2 uv;
  fragmentAttributes.getVec2("uv", uv);
  uv.y = 1.0f - uv.y;

  glm::vec3 lightPos(0, 1, 1);
  float att = glm::clamp(glm::dot(normal, glm::normalize(lightPos)), 0.0f, 1.0f);

  ae::Texture *tex = (ae::Texture*) uniforms.getTexture("tex");
  glm::vec4 texColor = tex->sample(uv.x, uv.y);
  return glm::vec4(att * texColor.xyz(), 1);
}

int main()
{
  GameObject luigi;
  luigi.addComponent<Transform>();
  luigi.addComponent<Mesh>();
  luigi.getComponent<Mesh>()->loadFromFile("./luigi-lowpoly.obj");

  Window window(0, 0, Window::getMaxWidth(), Window::getMaxHeight());

  Framebuffer fb(window.getWidth(), window.getHeight());
  fb.clearBuffers();

  Pipeline pl;
  pl.program.fragmentShader = fshader;
  pl.program.vertexShader = vshader;

  float rotation = 0.0f;

  glm::mat4 P = glm::perspective(M_PI/3.0, double(fb.getWidth()) / fb.getHeight(), 0.5, 40.0);
  P = glm::scale(glm::mat4(1.0f), glm::vec3(1,0.6,1)) * P;
  pl.program.uniforms.set("P", P);
  pl.program.uniforms.set("screenWidth", fb.getWidth());
  pl.program.uniforms.set("screenHeight", fb.getHeight());

  static float trans = 0.0f;
  static float cameraX = 0.0f, cameraZ = 0.0f;

  ae::Texture *texture = new ae::Texture();
  texture->loadFromFile("luigiD.jpg");
  pl.program.uniforms.set("tex", texture);

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

    fb.clearBuffers();

    glm::mat4 V(1.0f);
    V = glm::lookAt(glm::vec3(cameraX,0,cameraZ),glm::vec3(cameraX,0,cameraZ-20),glm::vec3(0,1,0));
    pl.program.uniforms.set("V", V);

    trans += 0.05;
    rotation += 0.005f;

    glm::mat4 M(1.0f);

    Transform& t = *(luigi.getComponent<Transform>());
    t.position =  glm::vec3(-12,-8, ((sin(trans)*0.5+0.5f)*-37)-1);
    t.rotation = glm::angleAxis(rotation*5, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.15);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), fb);

    t.position =   glm::vec3(((sin(trans*0.5f))*3),-15,-20);
    t.rotation = glm::angleAxis( rotation*9, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), fb);

    t.position =  glm::vec3(12,-8,-13);
    t.rotation = glm::angleAxis(rotation*14, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), fb);


    window.render(fb);
    window.display();

    Debug::showWindow();
  }

  getch();
  endwin();
}

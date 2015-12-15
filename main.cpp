#include <ncurses.h>
#include <stdlib.h>

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

  Texture *tex = uniforms.getTexture("tex");
  glm::vec4 texColor = tex->sample(uv.x, uv.y);
  return glm::vec4(att * texColor.xyz(), 1);
}

int main()
{
  Window window(0, 0, Window::getMaxWidth(), Window::getMaxHeight() * 0.9);

  Framebuffer fb(window.getWidth(), window.getHeight());
  fb.clearBuffers();

  Pipeline pl;
  pl.program.fragmentShader = fshader;
  pl.program.vertexShader = vshader;

  std::vector<glm::vec3> pos, normals;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> colors;
  bool triangles;
  FileReader::ReadOBJ("./luigi-lowpoly.obj", pos, uvs, normals, triangles);
  float minx = 99999, maxx = -99999, miny = 99999, maxy = -99999, minz = 99999, maxz = -99999;

  for(int i = 0; i < pos.size(); ++i)
  {
    minx = std::min(minx, pos[i].x);
    maxx = std::max(maxx, pos[i].x);
    miny = std::min(miny, pos[i].y);
    maxy = std::max(maxy, pos[i].y);
    minz = std::min(minz, pos[i].z);
    maxz = std::max(maxz, pos[i].z);
  }

  for(int i = 0; i < pos.size(); ++i)
  {
    glm::vec3 color = pos[i];
    color.x = (color.x - minx) / (maxx - minx);
    color.y = (color.y - miny) / (maxy - miny);
    color.z = (color.z - minz) / (maxz - minz);
    colors.push_back(color);
  }

  VAO vao;
  vao.addVBO("position", pos);
  vao.addVBO("color", colors);
  vao.addVBO("normal", normals);
  vao.addVBO("uv", uvs);

  float rotation = 0.0f;

  glm::mat4 P = glm::perspective(M_PI/3.0, double(fb.getWidth()) / fb.getHeight(), 0.5, 40.0);
  P = glm::scale(glm::mat4(1.0f), glm::vec3(1,0.6,1)) * P;
  pl.program.uniforms.set("P", P);
  pl.program.uniforms.set("screenWidth", fb.getWidth());
  pl.program.uniforms.set("screenHeight", fb.getHeight());

  static float trans = 0.0f;
  static float cameraX = 0.0f, cameraZ = 0.0f;

  Texture *texture = new Texture();
  texture->loadFromFile("luigiD.jpg");
  pl.program.uniforms.set("tex", texture);

  for (int i = 0; i < 10000; ++i) //while (true)
  {
    //wattron(window, COLOR_PAIR(70));
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

    Transform t;
    t.position =  glm::vec3(-12,-8, ((sin(trans)*0.5+0.5f)*-37)-1);
    t.rotation = glm::angleAxis(rotation*5, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.15);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    t.position =   glm::vec3(((sin(trans*0.5f))*3),-15,-20);
    t.rotation = glm::angleAxis( rotation*9, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    t.position =  glm::vec3(12,-8,-13);
    t.rotation = glm::angleAxis(rotation*14, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    window.render(fb);
    window.display();

    Debug::showWindow();
  }

  endwin();
}

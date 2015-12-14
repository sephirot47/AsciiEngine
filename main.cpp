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
#include "VAO.h"

#include "GameObject.h"

using namespace std;
using namespace agl;

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

class Transform : public Component
{
public:
  Transform() { }

  void mec() { name = name + "MEC"; }
};

int main()
{
  GameObject go;
  Transform *t = go.addComponent<Transform>("transform");
  t->mec();
  go.removeComponent<Transform>("transformME");
  std::cout << go.getComponent<Transform>("transformMEC")->name << std::endl;

  Window window(0, 0, Window::getMaxWidth(), Window::getMaxHeight() * 0.9);
  Window debugWindow(Window::getMaxWidth() * 0.05, Window::getMaxHeight() * 0.9,
                     Window::getMaxWidth() * 0.9, Window::getMaxHeight() * 0.1);
  debugWindow.drawBox = true;
  Window profWindow(15, 10, 20, 12); profWindow.drawBox = true;

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
    //*/
    //wattron(window, COLOR_PAIR(70));
    window.erase();
    debugWindow.erase();
    profWindow.erase();
    int ch = getch();
    if (ch == 'a') {
      profWindow.printf(0,3,"LEFT   ");
      cameraX += 0.5f;
    } else if (ch == 'd') {
        profWindow.printf(0,3,"RIGHT   ");
      cameraX -= 0.5f;
    } else if (ch == 'w') {
        profWindow.printf(0,3,"FORWARD   ");
      cameraZ += 0.5f;
    } else if (ch == 's') {
      profWindow.printf(0,3,"BACKWARDS  ");
      cameraZ -= 0.5f;
    } else {
      profWindow.printf(0,3,"NONE   ");
    }
    //*/
    auto frameStart = std::chrono::system_clock::now();
    fb.clearBuffers();

    glm::mat4 V(1.0f);
    V = glm::lookAt(glm::vec3(cameraX,0,cameraZ),glm::vec3(cameraX,0,cameraZ-20),glm::vec3(0,1,0));
    pl.program.uniforms.set("V", V);

    trans += 0.05;
    rotation += 0.005f;
    glm::mat4 M(1.0f);
    M = glm::translate(M, glm::vec3(-12,-8, ((sin(trans)*0.5+0.5f)*-37)-1));
    M = glm::rotate(M, rotation*5, glm::vec3(0,1,0));
    M = glm::scale(M,glm::vec3(0.15));

    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(((sin(trans*0.5f))*3),-15,-20));
    M = glm::rotate(M, rotation*9, glm::vec3(0,1,0));
    M = glm::scale(M,glm::vec3(0.2));

    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(12,-8,-13));
    M = glm::rotate(M, rotation*14, glm::vec3(0,1,0));
    M = glm::scale(M,glm::vec3(0.2));

    pl.program.uniforms.set("M", M);
    pl.drawVAO(vao, fb);

    window.render(fb);
    window.display();

    debugWindow.printf(0,0,"WOLOLOO");
    debugWindow.display();

    auto frameEnd = std::chrono::system_clock::now();
    profWindow.printf(0,0,"%f fps",1000.0f/std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count());
    profWindow.printf(0,1,"%f ",cameraX);
    profWindow.printf(0,2,"%c", ch);
    profWindow.display();
  }

  //getch();
  endwin();
}

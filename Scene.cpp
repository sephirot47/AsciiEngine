#include "Scene.h"

using namespace ae;

glm::vec4 vshader(const agl::GenericMap &vertexAttributes, const agl::GenericMap &uniforms, agl::GenericMap &fragmentAttributes)
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

glm::vec4 fshader(const agl::GenericMap &fragmentAttributes, const agl::GenericMap &uniforms)
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

Scene::Scene()
{
  pl.program.fragmentShader = fshader;
  pl.program.vertexShader = vshader;

  luigi.addComponent<Transform>();
  luigi.addComponent<Mesh>();
  luigi.getComponent<Mesh>()->loadFromFile("./luigi-lowpoly.obj");

  ae::Texture *texture = new ae::Texture();
  texture->loadFromFile("luigiD.jpg");
  pl.program.uniforms.set("tex", texture);
}

void Scene::render(agl::Framebuffer &framebuffer)
{
    static float trans = 0.0f, rotation = 0.0f;

    glm::mat4 P = glm::perspective(M_PI/3.0,
                                   double(framebuffer.getWidth()) / framebuffer.getHeight(),
                                   0.5,
                                   40.0);
    P = glm::scale(glm::mat4(1.0f), glm::vec3(1,0.6,1)) * P;
    pl.program.uniforms.set("P", P);
    pl.program.uniforms.set("screenWidth", framebuffer.getWidth());
    pl.program.uniforms.set("screenHeight", framebuffer.getHeight());

    glm::mat4 V(1.0f);
    V = glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,-20),glm::vec3(0,1,0));
    pl.program.uniforms.set("V", V);

    trans += 0.05;
    rotation += 0.005f;

    glm::mat4 M(1.0f);

    framebuffer.clearBuffers();

    Transform& t = *(luigi.getComponent<Transform>());
    t.position =  glm::vec3(-12, -8, ((sin(trans)*0.5+0.5f)*-37)-1);
    t.rotation = glm::angleAxis(rotation*5, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.15);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), framebuffer);

    t.position =   glm::vec3(((sin(trans*0.5f))*3),-15,-20);
    t.rotation = glm::angleAxis( rotation*9, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), framebuffer);

    t.position =  glm::vec3(12,-8,-13);
    t.rotation = glm::angleAxis(rotation*14, glm::vec3(0,1,0));
    t.scale = glm::vec3(0.2);
    t.getModelMatrix(M);
    pl.program.uniforms.set("M", M);
    pl.drawVAO(*(luigi.getComponent<Mesh>()->getVAO()), framebuffer);
}

void Scene::addGameObject(GameObject &go)
{
    gameObjects.push_back(go);
}

GameObject* Scene::getGameObject(const std::string &name)
{
    for(unsigned int i = 0; i < gameObjects.size(); ++i)
    {
        if(gameObjects[i].name == name) return &(gameObjects[i]);
    }
    return nullptr;
}

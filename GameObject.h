#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <typeindex>

#include "AsciiGL/AsciiGL.h"
#include "Component.h"

namespace ae
{

class GameObject
{
private:
  std::map<std::type_index, std::vector<Component*>> components;

public:

  std::string name; //gameObject identifier name

  GameObject();

  template <class T> T* addComponent()
  {
    return addComponent<T>("");
  }

  template <class T> T* addComponent(const std::string &name)
  {
    auto x = components.find(typeid(T));
    if(x == components.end()) components[typeid(T)] = std::vector<Component*>();

    components[typeid(T)].push_back(new T());
    int s = components[typeid(T)].size();
    if(name != "") components[typeid(T)][s-1]->name = name;
    return (T*)(components[typeid(T)][s-1]);
  }

  template <class T> T* getComponent()
  {
    auto x = components.find(typeid(T));
    if(x != components.end()) return (T*)(x->second[0]);
    return nullptr;
  }

  template <class T> T* getComponent(const std::string &name)
  {
    auto x = components.find(typeid(T));
    if(x != components.end())
    {
      for(int i = 0; i < x->second.size(); ++i)
        if(x->second[i]->name == name) return (T*)(&(x->second[i]));
    }
    return nullptr;
  }

  template <class T> void removeComponent()
  {
    auto v = components.find(typeid(T));
    if(v != components.end()) v->second.erase(v->second.end()-1);
  }

  template <class T> void removeComponent(const std::string &name)
  {
    auto v = components.find(typeid(T));
    for(int i = 0; i < v->second.size(); ++i)
    {
      if(v->second[i]->name == name) v->second.erase(v->second.begin() + i);
    }
  }
};

}

#endif // GAMEOBJECT_H

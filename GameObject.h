#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "Component.h"

class GameObject
{
private:
  std::map<std::type_index, std::vector<Component*>> components;

public:
  GameObject();
  template <class T> T* addComponent()
  {
    return addComponent<T>("");
  }

  template <class T> T* addComponent(const std::string &name)
  {
    T* comp = new T;
    auto x = components.find(typeid(T));
    if(x == components.end())
      components[typeid(T)] = std::vector<Component*>();

    if(name != "") comp->name = name;
    components[typeid(T)].push_back(comp);
  }

  template <class T> T* getComponent()
  {
    auto x = components.find(typeid(T));
    if(x != components.end()) return x->second[0];
    return nullptr;
  }

  template <class T> T* getComponent(const std::string &name)
  {
    auto v = components.find(typeid(T));
    if(v != components.end())
    {
      for(T comp : *v) if(comp.name == name) return comp;
    }
    return nullptr;
  }

  template <class T> void removeComponent()
  {
    auto v = components.find(typeid(T));
    if(v != components.end()) {
      delete (v->second[v->second.size()-1]);
      v->second.pop_back();
    }
  }

  template <class T> void removeComponent(const std::string &name)
  {
    auto v = components.find(typeid(T));
    for(int i = 0; i < v->second.size(); ++i)
    {
      if(v->second[i]->name == name) {
        delete (v->second[i]);
        v->second.erase(v->second.begin() + i);
      }
    }
  }
};

#endif // GAMEOBJECT_H

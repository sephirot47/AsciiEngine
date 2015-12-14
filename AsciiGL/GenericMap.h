#ifndef GENERICMAP_H
#define GENERICMAP_H

#include <map>
#include <vector>
#include <iostream>

#include "Texture.h"
#include "glm/glm.hpp"

namespace agl 
{
class GenericMap
{
private:
    std::map<std::string, bool>      map_bool;
    std::map<std::string, int>       map_int;
    std::map<std::string, float>     map_float;
    std::map<std::string, double>    map_double;
    std::map<std::string, glm::vec2> map_vec2;
    std::map<std::string, glm::vec3> map_vec3;
    std::map<std::string, glm::vec4> map_vec4;
    std::map<std::string, glm::mat2> map_mat2;
    std::map<std::string, glm::mat3> map_mat3;
    std::map<std::string, glm::mat4> map_mat4;
    std::map<std::string, Texture*> map_textures;

public:
    GenericMap();

    void set(const std::string& name, bool   value);
    void set(const std::string& name, int    value);
    void set(const std::string& name, float  value);
    void set(const std::string& name, double value);
    void set(const std::string& name, const glm::vec2& value);
    void set(const std::string& name, const glm::vec3& value);
    void set(const std::string& name, const glm::vec4& value);
    void set(const std::string& name, const glm::mat2& value);
    void set(const std::string& name, const glm::mat3& value);
    void set(const std::string& name, const glm::mat4& value);
    void set(const std::string& name, Texture *texture);

    bool   getBool  (const std::string& name) const;
    int    getInt   (const std::string& name) const;
    float  getFloat (const std::string& name) const;
    double getDouble(const std::string& name) const;
    void getVec2(const std::string& name, glm::vec2& vec2) const;
    void getVec3(const std::string& name, glm::vec3& vec3) const;
    void getVec4(const std::string& name, glm::vec4& vec4) const;
    void getMat2(const std::string& name, glm::mat2& mat2) const;
    void getMat3(const std::string& name, glm::mat3& mat3) const;
    void getMat4(const std::string& name, glm::mat4& mat4) const;
    Texture* getTexture(const std::string& name) const;

    static void interpolateTriangle(const std::vector<GenericMap> &attributes, const glm::vec3 &ws,
                                    GenericMap &interpolatedMap);
    static void interpolateLine(const std::vector<GenericMap>, float w,
                                GenericMap &interpolatedMap);
};
}

#endif // GENERICMAP_H

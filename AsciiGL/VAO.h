#ifndef VAO_H
#define VAO_H

#include <vector>
#include <map>
#include <tuple>

#include "GenericMap.h"

#include "glm/glm.hpp"


namespace agl {

class Pipeline;

class VAO
{

friend class Pipeline;

private:
    std::vector<GenericMap> vertexAttributes;

public:

    VAO();

    //TO DO check if adding VBOs of different size
    template<class T>
    void addVBO(const std::string &name, const std::vector<T> &data)
    {
        if(vertexAttributes.size() == 0) vertexAttributes = std::vector<GenericMap>(data.size());
        for(unsigned int i = 0; i < data.size(); ++i) vertexAttributes[i].set(name, data[i]);
    }

    //TO DO (V2.0) void removeVBO(std::string name);
};
}

#endif // VAO_H

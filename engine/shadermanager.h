#ifndef SHADERMANAGER_H_INCLUDE
#define SHADERMANAGER_H_INCLUDE

#include <map>
#include <string>

#include <GL/glew.h>

#include "util/shader.h"

class ShaderManager final
{
private:
  ShaderManager() {}
public:
  static inline ShaderManager& getInstance()
  {
    static ShaderManager man;
    return man;
  }

  ~ShaderManager();

  static const Shader* getShader(const std::string& name)
  {
    ShaderManager& sm = getInstance();
    auto it = sm.shaders.find(name);
    if (it == std::end(sm.shaders))
      it = sm.shaders.insert(std::make_pair(name, new Shader(name))).first;
    return it->second;
  }

private:
  std::map<std::string, Shader* > shaders;
};

#endif

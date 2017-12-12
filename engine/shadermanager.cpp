#include "shadermanager.h"

ShaderManager::~ShaderManager()
{
  for (auto it : shaders)
    delete it.second;
}

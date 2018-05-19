#ifndef VISAGEMESH_H_INCLUDE
#define VISAGEMESH_H_INCLUDE

#include "visage.h"

#include <string>
#include <vector>

#include <stdint.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../meshmanager.h"

namespace thomas
{
namespace visage
{
enum class TextureType
{
  DIFFUSE,
  SPECULAR,
  EMISSION
};
class VisageMesh : public Visage
{
public:
  VisageMesh() : mesh(nullptr), diffuse(0), specular(0), emission(0) {}
  virtual ~VisageMesh() {}

  virtual inline Type type() const { return Type::MESH; }

  virtual void draw();

  void load(const std::string& name);
  void attach(const TextureType type, const std::string& name);

protected:
  Mesh* mesh;
  GLint diffuse;
  GLint specular;
  GLint emission;
};
}
}

#endif

#ifndef SKYBOX_H_INCLUDE
#define SKYBOX_H_INCLUDE

#include <string>

#include <GL/glew.h>

#include "visage.h"

class VisageSkybox : public Visage
{
public:
  VisageSkybox() : textures{0}, skybox_vao(0), skybox_vbo(0) {}
  virtual ~VisageSkybox();

  virtual inline Type type() const { return Type::SKYBOX; }

  virtual void draw();

  void load(const std::string& name);

private:
  GLuint textures[6];
  GLuint skybox_vao;
  GLuint skybox_vbo;
  GLuint skybox_ebo;
};

#endif

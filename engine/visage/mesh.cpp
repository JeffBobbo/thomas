#include "mesh.h"

#include "../texturemanager.h"
#include "../shader.h"

void VisageMesh::draw()
{
  Visage::draw();

  GLint uni = 0;
  glActiveTexture(GL_TEXTURE0);
  if (diffuse && (uni = glGetUniformLocation(engine::Program::active()->handle(), "diffuse")) >= 0)
  {
    glBindTexture(GL_TEXTURE_2D, diffuse);
    glUniform1i(uni, 0);
  }
  glActiveTexture(GL_TEXTURE1);
  if (specular && (uni = glGetUniformLocation(engine::Program::active()->handle(), "specular")) >= 0)
  {
    glBindTexture(GL_TEXTURE_2D, specular);
    glUniform1i(uni, 1);
  }
  else
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  glActiveTexture(GL_TEXTURE2);
  if (emission && (uni = glGetUniformLocation(engine::Program::active()->handle(), "emission")) >= 0)
  {
    glBindTexture(GL_TEXTURE_2D, emission);
    glUniform1i(uni, 2);
  }
  else
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  glBindVertexArray(mesh->getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO());
  glDrawElements(GL_TRIANGLES, mesh->getIndicies().size(), GL_UNSIGNED_INT, (void*)0);
}

void VisageMesh::load(const std::string& name)
{
  mesh = const_cast<Mesh*>(MeshManager::getMesh(name));
}

void VisageMesh::attach(const TextureType type, const std::string& name)
{
  GLint t = TextureManager::getTexture(name);
  switch (type)
  {
    case TextureType::DIFFUSE:
      diffuse = t;
    break;
    case TextureType::SPECULAR:
      specular = t;
    break;
    case TextureType::EMISSION:
      emission = t;
    break;
  }
}

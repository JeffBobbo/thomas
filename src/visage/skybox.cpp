#include <visage/skybox.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <object/camera.h>
#include <meshmanager.h>
#include <shader.h>
#include <texturemanager.h>

using namespace thomas::visage;

VisageSkybox::~VisageSkybox()
{
  if (textures[0])
    glDeleteTextures(6, textures);

  if (skybox_vbo)
    glDeleteBuffers(1, &skybox_vbo);
  if (skybox_ebo)
    glDeleteBuffers(1, &skybox_ebo);
  if (skybox_vao)
    glDeleteBuffers(1, &skybox_vao);

}

void VisageSkybox::draw()
{
  Visage::draw();

  GLboolean oldCull = glIsEnabled(GL_CULL_FACE);

  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  glBindVertexArray(skybox_vao);
  glActiveTexture(GL_TEXTURE0);

  for (int i = 0; i < 6; ++i)
  {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i*6*sizeof(GLuint)));
  }

  if (oldCull)
    glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
}

void VisageSkybox::load(const std::string& name)
{
  glGenTextures(6, textures);
  std::string suffixes[] = {"ft", "bk", "lf", "rt", "up", "dn"};
  for (int i = 0; i < 6; ++i)
  {
    textures[i] = TextureManager::getTexture(std::string(name + "_" + suffixes[i] + ".png"));
  }

  // TODO: This mesh is broken, some faces have incorrect windings
  // Ideally import a cube for it from an .obj, but need one setup properly
  const static float vertices[] = {
    // x, y, z, u, v, nx, ny, nz
    // front
    -100.0f, -100.0f,  100.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     100.0f, -100.0f,  100.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     100.0f,  100.0f,  100.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
    -100.0f,  100.0f,  100.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
    // back
     100.0f, -100.0f, -100.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -100.0f, -100.0f, -100.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    -100.0f,  100.0f, -100.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
     100.0f,  100.0f, -100.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
    // left
     100.0f, -100.0f,  100.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
     100.0f, -100.0f, -100.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
     100.0f,  100.0f, -100.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
     100.0f,  100.0f,  100.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    // right
    -100.0f, -100.0f,  100.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
    -100.0f, -100.0f, -100.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
    -100.0f,  100.0f, -100.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
    -100.0f,  100.0f,  100.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
    // up
    -100.0f,  100.0f, -100.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     100.0f,  100.0f, -100.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     100.0f,  100.0f,  100.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -100.0f,  100.0f,  100.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
    // down
    -100.0f, -100.0f,  100.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     100.0f, -100.0f,  100.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     100.0f, -100.0f, -100.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
    -100.0f, -100.0f, -100.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f
  };

  const static GLuint elements[] = {
    // front
    0, 1, 2,
    2, 3, 0,
    // back
    4, 5, 6,
    6, 7, 4,
    // left
    8, 9, 10,
    10, 11, 8,
    // right
    12, 13, 14,
    14, 15, 12,
    // up
    16, 17, 18,
    18, 19, 16,
    // down
    20, 21, 22,
    22, 23, 20
  };

  glGenVertexArrays(1, &skybox_vao);
  glBindVertexArray(skybox_vao);

  glGenBuffers(1, &skybox_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &skybox_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skybox_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(5*sizeof(float)));
  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

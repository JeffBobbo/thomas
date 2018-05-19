#ifndef MESHMANAGER_H_INCLUDE
#define MESHMANAGER_H_INCLUDE

#include <string>
#include <map>
#include <vector>

#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <tiny_obj_loader.h>

class Mesh final
{
  Mesh() : materials(), vbo_v(nullptr), vbo_t(nullptr), vbo_n(nullptr), ebo(nullptr), vao(nullptr) {}
public:
  Mesh(const std::vector<tinyobj::shape_t >& shapes, const std::vector<tinyobj::material_t >& m);
  ~Mesh();

  inline size_t getNumMeshes() const { return meshes.size(); }
  inline size_t getIndexCount(const size_t i) const { return meshes[i].indices.size(); }
  inline const GLuint& getEBO(const size_t i) const { return ebo[i]; }
  inline const GLuint& getVAO(const size_t i) const { return vao[i]; }
  inline const tinyobj::material_t& getMaterial(const size_t i) const { return materials[i]; }
  //inline const tinyobj::mesh_t& getMesh(const ssize_t i) const {meshes[i]; }

private:
  std::vector<tinyobj::mesh_t > meshes;
  std::vector<tinyobj::material_t > materials;

  GLuint* vbo_v;
  GLuint* vbo_t;
  GLuint* vbo_n;

  GLuint* ebo;
  GLuint* vao;
};

class MeshManager final
{
private:
  MeshManager() {}
public:
  static inline MeshManager& getInstance()
  {
    static MeshManager man;
    return man;
  }

  ~MeshManager();

  static const Mesh* getMesh(const std::string& name);

  static void loadFile(const std::string& file);
private:
  std::map<std::string, Mesh* > meshes;
};


#endif

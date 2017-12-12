#ifndef MESHMANAGER_H_INCLUDE
#define MESHMANAGER_H_INCLUDE

#include <string>
#include <map>
#include <vector>

#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*
struct Face final
{
  size_t vertices[3];
  size_t uvs[3];
  size_t normals[3];
};
 */

class Mesh final
{
public:
  Mesh() : vbo_v(0), vbo_t(0), vbo_n(0), ebo(0), vao(0) {}
  Mesh(const std::string& name);
  ~Mesh();

  inline const std::vector<int32_t >& getIndicies() const { return indicies; }
  inline const std::vector<glm::vec3>& getVertices() const { return vertices; }
  inline const std::vector<glm::vec2>& getUVCoords() const { return uvCoords; }
  inline const std::vector<glm::vec3>& getNormals() const { return normals; }

  inline const GLuint& getVBO_V() const { return vbo_v; }
  inline const GLuint& getVBO_T() const { return vbo_t; }
  inline const GLuint& getVBO_N() const { return vbo_n; }
  inline const GLuint& getEBO() const { return ebo; }
  inline const GLuint& getVAO() const { return vao; }

private:
  std::vector<int32_t > indicies;
  std::vector<glm::vec3 > vertices;
  std::vector<glm::vec2 > uvCoords;
  std::vector<glm::vec3 > normals;
  //std::vector<Face> faces;

  GLuint vbo_v;
  GLuint vbo_t;
  GLuint vbo_n;
  GLuint ebo;
  GLuint vao;
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

  static const Mesh* getMesh(const std::string& name)
  {
    MeshManager& mm = getInstance();
    auto it = mm.meshes.find(name);
    if (it == std::end(mm.meshes))
      it = mm.meshes.insert(std::make_pair(name, new Mesh(name))).first;
    return it->second;
  }

private:
  std::map<std::string, Mesh* > meshes;
};


#endif

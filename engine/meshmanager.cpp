#include "meshmanager.h"

#include <fstream>
#include <map>

#include <cstring> // std::memcmp

#include <iostream>

Mesh::~Mesh()
{
  glBindVertexArray(0);
  glDeleteBuffers(meshes.size(), vbo_v);
  glDeleteBuffers(meshes.size(), vbo_t);
  glDeleteBuffers(meshes.size(), vbo_n);
  glDeleteBuffers(meshes.size(), ebo);
  glDeleteVertexArrays(meshes.size(), vao);
  delete[] vbo_v;
  delete[] vbo_t;
  delete[] vbo_n;
  delete[] ebo;
  delete[] vao;
}

Mesh::Mesh(const std::vector<tinyobj::shape_t >& shapes, const std::vector<tinyobj::material_t >& m)
{
  materials = m;

  meshes.reserve(shapes.size());
  vao = new GLuint[shapes.size()];
  vbo_v = new GLuint[shapes.size()];
  vbo_t = new GLuint[shapes.size()];
  vbo_n = new GLuint[shapes.size()];
  ebo = new GLuint[shapes.size()];
  glGenVertexArrays(shapes.size(), vao);
  glGenBuffers(shapes.size(), vbo_v);
  glGenBuffers(shapes.size(), vbo_t);
  glGenBuffers(shapes.size(), vbo_n);
  glGenBuffers(shapes.size(), ebo);

  float longest = 0.0f;
  for (size_t i = 0; i < shapes.size(); ++i)
  {
    tinyobj::shape_t s = shapes[i];
    tinyobj::mesh_t& mesh = s.mesh;

    for (size_t i = 0; i < mesh.positions.size(); i += 3)
    {
      float l = mesh.positions[i  ]*mesh.positions[i  ] +
                mesh.positions[i+1]*mesh.positions[i+1] +
                mesh.positions[i+2]*mesh.positions[i+2];

      if (l > longest)
        longest = l;
    }
  }
  longest = std::sqrt(longest);

  for (size_t i = 0; i < shapes.size(); ++i)
  {
    tinyobj::shape_t s = shapes[i];
    tinyobj::mesh_t& mesh = s.mesh;

    for (size_t i = 0; i < mesh.positions.size(); ++i)
      mesh.positions[i] /= longest;

    meshes.push_back(mesh);

    glBindVertexArray(vao[i]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_v[i]);
    glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), &(mesh.positions[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );

    glBindBuffer(GL_ARRAY_BUFFER, vbo_t[i]);
    glBufferData(GL_ARRAY_BUFFER, mesh.texcoords.size() * sizeof(float), &(mesh.texcoords[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );

    glBindBuffer(GL_ARRAY_BUFFER, vbo_n[i]);
    glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), &(mesh.normals[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &(mesh.indices[0]), GL_STATIC_DRAW);

    /*

    for (material_t& mat : materials)
    {
      if (mat.ambient_texname.length())
        TextureManager::getInstane().getTexture(mat.ambient_texname);
      if (mat.diffuse_texname.length())
        TextureManager::getInstane().getTexture(mat.diffuse_texname)
      if (mat.specular_texname.length())
        TextureManager::getInstane().getTexture(mat.specular_texname)
      //if (mat.specular_highlight_texname.length())
        //TextureManager::getInstane().getTexture(mat.specular_highlight_texname)
      //if (mat.bump_texname.length())
        //TextureManager::getInstane().getTexture(mat.bump_texname)
      //if (mat.displacement_texname.length())
        //TextureManager::getInstane().getTexture(mat.displacement_texname)
      //if (mat.reflection_texname.length())
        //TextureManager::getInstane().getTexture(mat.reflection_texname)
      //if (mat.alpha_texname.length())
        //TextureManager::getInstane().getTexture(mat.alpha_texname)
    }
     */
  }
}


MeshManager::~MeshManager()
{
  for (auto v : meshes)
  {
    delete v.second;
  }
}

const Mesh* MeshManager::getMesh(const std::string& name)
{
  MeshManager& mm = getInstance();
  auto it = mm.meshes.find(name);
  if (it == std::end(mm.meshes))
    throw std::string("No known mesh: ") + name;
  return it->second;
}

void MeshManager::loadFile(const std::string& file)
{
  std::vector<tinyobj::shape_t > shapes;
  std::vector<tinyobj::material_t > materials;
  std::string error = tinyobj::LoadObj(shapes, materials, file.c_str());
  if (error.size())
  {
    std::cerr << error << std::endl;
    throw error;
  }

  MeshManager& mm = getInstance();
  mm.meshes.insert(std::make_pair(file, new Mesh(shapes, materials)));
}

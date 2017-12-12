#include "meshmanager.h"

#include <fstream>
#include <map>

#include <cstring> // std::memcmp

struct VertexTriplet
{
  glm::vec3 v;
  glm::vec2 t;
  glm::vec3 n;

  inline bool operator<(const VertexTriplet& other) const
  {
    return std::memcmp(static_cast<const void*>(this), static_cast<const void*>(&other), sizeof(VertexTriplet)) > 0;
  }
};

int32_t findSimilar(const VertexTriplet& vt, const std::map<VertexTriplet, int32_t >& vtMap)
{
  auto it = vtMap.find(vt);
  if (it != std::end(vtMap))
    return it->second;
  return -1;
}

void counts(const std::string& fname,
            uint32_t& vCount,
            uint32_t& tCount,
            uint32_t& nCount,
            uint32_t& fCount)
{
  std::ifstream ifs(fname);
  if (!ifs.good())
    throw std::string("Failed to read ") + fname;

  while (ifs.good())
  {
    char input;
    ifs.get(input);
    if (input == 'v')
    {
      ifs.get(input);
      if (input == ' ')
        ++vCount;
      else if (input == 't')
        ++tCount;
      else if (input == 'n')
        ++nCount;
    }
    else if (input == 'f')
    {
      ifs.get(input);
      if (input == ' ')
        ++fCount;
    }

    ifs.get();
    while (input != '\n')
      ifs.get(input);
    ifs.get();
  }
  ifs.close();
}

struct Face
{
  std::size_t vIndicies[3];
  std::size_t tIndicies[3];
  std::size_t nIndicies[3];
};
void load2(const std::string& fname)
{

  std::vector<glm::vec3 > vertices;
  std::vector<glm::vec2 > uvs;
  std::vector<glm::vec3 > normals;
  std::vector<Face > faces;

  // this bit is optional, it means parsing the file twice
  // but means we can allocate everything upfront
  // which should be a lot faster
  uint32_t vCount = 0, tCount = 0, nCount = 0, fCount = 0;
  counts(fname, vCount, tCount, nCount, fCount);
  vertices.reserve(vCount);
  uvs.reserve(tCount);
  normals.reserve(nCount);
  faces.reserve(fCount);

  std::size_t vIndex = 0, tIndex = 0, nIndex = 0, fIndex = 0;

  std::ifstream ifs(fname);
  if (!ifs.good()) // should never happen, because of counts()
    throw std::string("Failed to read ") + fname;

  while (ifs.good())
  {
    char input;
    ifs.get(input);
    if (input == 'v')
    {
      ifs.get(input);

      if (input == ' ')
      {
        glm::vec3 v;
        ifs >> v.x >> v.y >> v.z;
        vertices.push_back(v);
      }
    }
  }
}

void load(const std::string& fname,
          std::vector<glm::vec3 >& vertices,
          std::vector<glm::vec2 >& uvs,
          std::vector<glm::vec3 >& normals)
{
  std::vector<int32_t> vIndices, uvIndices, nIndices;
  std::vector<glm::vec3> tVertices;
  std::vector<glm::vec2> tUvCoords;
  std::vector<glm::vec3> tNormals;

  std::ifstream ifs(fname);
  if (!ifs.good())
    throw std::string("Failed to read ") + fname;
  while (ifs.good())
  {
    std::string token;
    ifs >> token;
    if (token == "v")
    {
      float v[3];
      ifs >> v[0] >> v[1] >> v[2];
      tVertices.push_back(glm::vec3(v[0], v[1], v[2]));
    }
    else if (token == "vt")
    {
      float vt[2];
      ifs >> vt[0] >> vt[1];
      tUvCoords.push_back(glm::vec2(vt[0], 1.0 - vt[1]));
    }
    else if (token == "vn")
    {
      float vn[3];
      ifs >> vn[0] >> vn[1] >> vn[2];
      tNormals.push_back(glm::vec3(vn[0], vn[1], vn[2]));
    }
    else if (token == "f")
    {
      //Face face;
      int i[9];
      ifs >> i[0];
      ifs.get();
      ifs >> i[3];
      ifs.get();
      ifs >> i[6];

      ifs >> i[1];
      ifs.get();
      ifs >> i[4];
      ifs.get();
      ifs >> i[7];

      ifs >> i[2];
      ifs.get();
      ifs >> i[5];
      ifs.get();
      ifs >> i[8];


      vIndices.push_back(i[0]);
      vIndices.push_back(i[1]);
      vIndices.push_back(i[2]);
      uvIndices.push_back(i[3]);
      uvIndices.push_back(i[4]);
      uvIndices.push_back(i[5]);
      nIndices.push_back(i[6]);
      nIndices.push_back(i[7]);
      nIndices.push_back(i[8]);
    }
    for (auto it : vIndices)
      vertices.push_back(tVertices[it-1]);
    for (auto it : uvIndices)
      uvs.push_back(tUvCoords[it-1]);
    for (auto it : nIndices)
      normals.push_back(tNormals[it-1]);
  }
}

void reindex(
           std::vector<glm::vec3 >& verticesIn,
           std::vector<glm::vec2 >& uvsIn,
           std::vector<glm::vec3 >& normalsIn,

           std::vector<int32_t >& indicies,
           std::vector<glm::vec3 >& vertices,
           std::vector<glm::vec2 >& uvs,
           std::vector<glm::vec3 >& normals)
{
  std::map<VertexTriplet, int32_t > vtMap;

  for (int32_t i = 0; i < static_cast<int32_t>(verticesIn.size()); ++i)
  {
    VertexTriplet vt = {verticesIn[i], uvsIn[i], normalsIn[i]};

    int32_t index = findSimilar(vt, vtMap);
    if (index >= 0)
    {
      indicies.push_back(index);
    }
    else
    {
      vertices.push_back(verticesIn[i]);
      uvs.push_back(uvsIn[i]);
      normals.push_back(normalsIn[i]);
      indicies.push_back(vertices.size() - 1);
      vtMap[vt] = vertices.size() - 1;
    }
  }
}

void rescale(std::vector<glm::vec3 >& vertices)
{
  float longest = 0.0f;

  for (auto& it : vertices)
  {
    if (it != glm::vec3(0.0f) && glm::length(it) > longest)
      longest = glm::length(it);
  }

  for (auto& it : vertices)
    it /= longest;
}

Mesh::~Mesh()
{
  glBindVertexArray(0);
  if (vbo_v)
    glDeleteBuffers(1, &vbo_v);
  if (vbo_t)
    glDeleteBuffers(1, &vbo_t);
  if (vbo_n)
    glDeleteBuffers(1, &vbo_n);
  if (ebo)
    glDeleteBuffers(1, &ebo);
  if (vao)
    glDeleteBuffers(1, &vao);
}

Mesh::Mesh(const std::string& fname)
{
  std::vector<glm::vec3 > v;
  std::vector<glm::vec2 > t;
  std::vector<glm::vec3 > n;
  load(fname, v, t, n);
  reindex(v, t, n, indicies, vertices, uvCoords, normals);
  rescale(vertices);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo_v);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );
  glGenBuffers(1, &vbo_t);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_t);
  glBufferData(GL_ARRAY_BUFFER, uvCoords.size() * sizeof(glm::vec2), &uvCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );
  glGenBuffers(1, &vbo_n);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_n);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), &indicies[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}


MeshManager::~MeshManager()
{
  for (auto it : meshes)
    delete it.second;
}

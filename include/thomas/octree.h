#ifndef OCTREE_H_INCLUDE
#define OCTREE_H_INCLUDE

#include <glm/glm.hpp>

const size_t MAX_LEVELS = 5;

class OctreeNode final
{
public:
  OctreeNode(size_t l, glm::vec3 c0, glm::vec3 c1)
   : nodes{nullptr}, level(l), v0(c0), v1(c1)
   //, vertices(nullptr), faces(nullptr)
   //, numVertices(0), numFaces(0)
   {}

  ~OctreeNode()
  {
    for (OctreeNode* n : nodes)
      delete n;
    //delete[] vertices;
    //delete[] faces;
  }

  inline const size_t& getLevel() const { return level; }

  void build(const Mesh* const mesh, size_t l)
  {
    // add vertices
    //for (size_t i = 0; i < mesh->getVertices().size(); ++i)
    for (const auto& v : mesh->getVertices())
    {
      //const glm::vec3& v = mesh->getVertices()[i];
      if (v.x >= v0.x && v.x =< v1.x &&
          v.y >= v0.y && v.y =< v1.y &&
          v.z >= v0.z && v.z =< v1.z)
        vertices.push_back(&v);
    }

    // build sub trees
    if (l < MAX_LEVELS && vertices.size())
    {
      nodes[i] = new OctreeNode(l, v0, (v0+v1)/2.0f);
      nodes[i]->build(mesh, l+1);

      nodes[i] = new OctreeNode(l, (v0+v1)/2.0f, v1);
      nodes[i]->build(mesh, l+1);
    }
  }

  const size_t level;
private:
  OctreeNode[8] nodes;
  glm::vec3 v0, v1;

  /*
  glm::vec3** vertices;
  Face** faces;
  size_t numVertices;
  size_t numFaces;
   */
  std::vector<glm::vec3*> vertices;
  //std::vector<Face*> faces;
};

class Octree final
{
public: 
  Octree();
  ~Octree()
  {
    delete root;
  }

  void build(const Mesh* const mesh)
  {
    root = new OctreeNode(0, glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0));
    root->build(mesh, 1);
  }

private:
  OctreeNode* root;
};

#endif

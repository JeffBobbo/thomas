#ifndef TEXTUREMANAGER_H_INCLUDE
#define TEXTUREMANAGER_H_INCLUDE

#include <map>
#include <string>

#include <GL/glew.h>

namespace thomas
{
class Texture final
{
public:
  Texture() : texture(0) {}
  Texture(const std::string& name);
  ~Texture();

  inline GLuint getTexture() const { return texture; }
private:
  GLuint texture;
};

class TextureManager final
{
private:
  TextureManager() {}
public:
  static inline TextureManager& getInstance()
  {
    static TextureManager man;
    return man;
  }

  ~TextureManager();

  static GLuint getTexture(const std::string& name)
  {
    TextureManager& tm = getInstance();
    auto it = tm.textures.find(name);
    if (it == std::end(tm.textures))
      it = tm.textures.insert(std::make_pair(name, new Texture(name))).first;
    return it->second->getTexture();
  }

private:
  std::map<std::string, Texture* > textures;
};
}

#endif

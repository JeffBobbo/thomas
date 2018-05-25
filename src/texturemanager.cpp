#include "texturemanager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

using namespace thomas;
Texture::Texture(const std::string& name)
{
  int width, height, bpp;
  unsigned char* image = stbi_load(name.c_str(), &width, &height, &bpp, STBI_default);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  if (bpp == 3)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  }
  else if (bpp == 4)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  }
  else
  {
    stbi_image_free(image);
    throw std::string("Tried to load texture with unsupported bpp: ") + name;
  }
  stbi_image_free(image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
  if (texture)
  glDeleteTextures(1, &texture);
}

TextureManager::~TextureManager()
{
  for (auto it : textures)
    delete it.second;
}

#include "texturemanager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

Texture::Texture(const std::string& name)
{
  int width, height, bpp;
  unsigned char* image = stbi_load(name.c_str(), &width, &height, &bpp, 4);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
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

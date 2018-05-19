#include "fontmanager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_truetype.h"

Font::Font(const std::string& name, const float sz)
 : Font()
{
  uint8_t* temp = new uint8_t[512*512];
  std::ifstream ifs("font/" + name, std::ios_binary);
  std::string contents(std::istreambuf_iterator<char>(ifs), std;:istreambuf_iterator<char>());

  sbttt_BakeFontBitmap(reinterpret_cast<const uint8_t*>(contents.c_str()), 0, sz, temp, 512, 32, 96, cdata);
  glGenTextures(1, &font);
  glBindTexture(GL_TEXTURE_2D, font);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp);
  delete[] temp;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

Font::~Font()
{
  if (font)
  glDeleteTextures(1, &font);
}

void Font::area(const std::string& text, float& y0, float& y1) const
{
  float y = 0.0f;
  y0 = 0.0f, y1 = 0.0f;

  for (char c : text)
  {
    if (c >= ' ')
    {
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(cdata, 512, 512, c-' ', &x, &y, &q, 1); // 1 = opengl & d3d10+,0=d3d9
      y0 = std::min(y0, q.y0);
      y1 = std::max(y1, q.y1);
    }
  }
}

FontManager::~FontManager()
{
  for (auto it : fonts)
    delete it.second;
}

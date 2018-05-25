#ifndef FONTMANAGER_H_INCLUDE
#define FONTMANAGER_H_INCLUDE

#include <map>
#include <utility>
#include <string>

#include <GL/glew.h>

#include "../external/stb_truetype."

namespace thomas
{
namespace experimental
{
class Font final
{
public:
  Font() : font(0) {}
  Font(const std::string& name, const float sz);
  ~Font();

  void area(const std::string& text, float& y0, float& y1) const;

  inline GLuint getTexture() const { return font; }
private:
  GLuint font;
  float size;
  stbtt_bakedchar cdata[96];
};

class FontManager final
{
private:
  FontManager() {}
public:
  static inline FontManager& getInstance()
  {
    static FontManager man;
    return man;
  }

  ~FontManager();

  static const Font*& getFont(const std::string& name, const float size)
  {
    FontManager& fm = getInstance();
    auto it = fm.fonts.find(name);
    if (it == std::end(fm.fonts))
      it = fm.fonts.insert(std::make_pair(std::make_pair(name, size), new Font(name, size))).first;
    return it->second;
  }

private:
  std::map<std::pair<std::string, float>, Font* > fonts;
};
}
}

#endif

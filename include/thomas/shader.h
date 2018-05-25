#ifndef SHADER_H_INCLUDE
#define SHADER_H_INCLUDE

#include <map>
#include <string>

#include <GL/glew.h>

namespace thomas
{
namespace object
{
class Camera;
}
class Shader final
{
public:
  Shader(const std::string& path, const GLenum t);
  ~Shader();

  // dislike this, allows bad stuff to happen
  inline GLuint handle() const { return shader; }
private:
  std::string infoLog() const;

  GLuint shader;
  const GLint type;
};

class ShaderManager final
{
private:
  ShaderManager() {}
  static inline ShaderManager& instance()
  {
    static ShaderManager m;
    return m;
  }
public:
  ~ShaderManager()
  {
    for (auto& it : shaders)
      delete it.second;
  }

  static const Shader* get(const std::string& path, const GLenum type)
  {
    ShaderManager& sm = instance();
    auto it = sm.shaders.find(path);
    if (it == std::end(sm.shaders))
      it = sm.shaders.insert(std::make_pair(path, new Shader(path, type))).first;
    return it->second;
  }

private:
  std::map<std::string, Shader* > shaders;
};

class Program
{
public:
  Program();
  ~Program();

  void attach(const std::string& name, const GLenum type) const;
  void link() const;

  // dislike this, allows bad stuff to happen
  inline GLuint handle() const { return program; }

  GLint uniform(const char* name) const;
  GLint attribute(const char* name) const;

  inline static const Program* active() { return current; }
  inline void activate() const
  {
    glUseProgram(handle());
    current = const_cast<Program* >(this);
  }

  void update(const thomas::object::Camera* const camera) const;

private:
  friend Shader;
  std::string infoLog() const;

  static Program* current;

  GLuint program;
};

class ProgramManager
{
private:
  ProgramManager() {}
  static inline ProgramManager& instance()
  {
    static ProgramManager m;
    return m;
  }
public:
  ~ProgramManager()
  {
    for (auto& it : programs)
      delete it.second;
  }

  static const Program* create(const std::string& name)
  {
    ProgramManager& pm = instance();
    auto it = pm.programs.find(name);
    if (it != std::end(pm.programs))
      throw std::string("Program already exists");
    Program* p = new Program();
    auto r = pm.programs.insert(std::make_pair(name, p));
    return r.first->second;
  }
  static const Program* get(const std::string& name)
  {
    ProgramManager& pm = instance();
    auto it = pm.programs.find(name);
    if (it == std::end(pm.programs))
      return nullptr;
    return it->second;
  }


private:
  std::map<std::string, Program* > programs;
};
}


#endif

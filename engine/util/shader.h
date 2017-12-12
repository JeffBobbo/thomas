#ifndef SHADER_H_INCLUDE
#define SHADER_H_INCLUDE

#include <string>

#include <GL/glew.h>

class Shader
{
public:
  Shader() : vertex(0), fragment(0), program(0) {};
  Shader(const std::string& name);
  ~Shader();

  inline const GLuint& handle() const { return program; }

  void activate() const;

  void update() const;

  void setLighting() const;

  static Shader* getActive();
private:
  void load(const std::string& sname, const std::string& vfname, const std::string& ffname);
  std::string name;

  GLuint vertex;   // id for vertex shader
  GLuint fragment; // id for fragment shader
  GLuint program;  // id for the shader program, used when rendering
};

#endif

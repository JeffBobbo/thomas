#include <shader.h>

#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <thomas.h>
#include <object/camera.h>

std::string readFile(const std::string& filename)
{
  std::ifstream in(filename);
  assert(in.good());
  return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}

namespace thomas
{
Program* active;

Shader::Shader(const std::string& path, const GLenum t)
 : shader(0)
 , type(t)
{
  std::string source = readFile(path);
  shader = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE)
    throw path + "\n" + Shader::infoLog();
}

Shader::~Shader()
{
  glDeleteShader(shader);
}

std::string Shader::infoLog() const
{
  GLsizei size = 0;
  std::string info;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
  info.resize(size);
  glGetShaderInfoLog(shader, size, &size, &info[0]);
  return info;
}

Program* Program::current = nullptr;

Program::Program()
 : program(0)
{
  program = glCreateProgram();
}

Program::~Program()
{
  glDeleteProgram(program);
}

void Program::attach(const std::string& name, const GLenum type) const
{
  const Shader* shader = ShaderManager::get(name, type);
  assert(shader);
  glAttachShader(program, shader->handle());
}

void Program::link() const
{
  glLinkProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status != GL_TRUE)
    throw infoLog();
}

GLint Program::uniform(const char* name) const
{
  GLint uni = glGetUniformLocation(handle(), name);

  //assert(uni >= 0);
  return uni;
}

GLint Program::attribute(const char* name) const
{
  GLint attrib = glGetAttribLocation(handle(), name);

  //assert(attrib >= 0);
  return attrib;
}

void Program::update(const object::Camera* const camera) const
{
  if (this != const_cast<const Program* >(current))
    activate();
  GLint uniView = glGetUniformLocation(handle(), "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera->getView()));

  GLint uniProj = glGetUniformLocation(handle(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(camera->getProjection(static_cast<float>(screenWidth), static_cast<float>(screenHeight))));

  GLint uniCam = glGetUniformLocation(handle(), "camera");
  if (uniCam >= 0)
    glUniform3fv(uniCam, 1, glm::value_ptr(camera->getPosition()));

  GLint uniGamma = glGetUniformLocation(handle(), "gamma");
  if (uniGamma >= 0)
    glUniform1f(uniGamma, 1.0);
}

std::string Program::infoLog() const
{
  GLsizei size = 0;
  std::string info;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
  info.resize(size);
  glGetProgramInfoLog(program, size, &size, &info[0]);
  return info;
}
}


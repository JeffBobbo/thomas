#include "shader.h"

#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../engine.h"
#include "../object/camera.h"

static std::string readFile(const char* const filename)
{
  std::ifstream in(filename);
  if (!in.good())
    throw std::string("Unable to open file: ") + filename;
  std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  return contents;
}

std::string infoLogShader(const GLuint id)
{
  GLsizei size = 0;
  std::string info;

  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
  info.resize(size);
  glGetShaderInfoLog(id, size, &size, &info[0]);
  return info;
}
std::string infoLogProgram(const GLuint id)
{
  GLsizei size = 0;
  std::string info;

  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &size);
  info.resize(size);
  glGetShaderInfoLog(id, size, &size, &info[0]);
  return info;
}

static GLuint compile(const GLint type, const char* source, const std::string& name)
{
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE)
  {
    std::stringstream ss;
    ss << "Failed to compile shader \"" << name << "\":" << std::endl;
    ss << infoLogShader(shader) << std::endl;
    std::cerr << ss.str() << std::endl;
    throw ss.str();
  }
  return shader;
}

Shader* active = nullptr;
Shader::Shader(const std::string& name)
  : Shader()
{
  if (name.length())
    load(name, "shaders/" + name + ".vert", "shaders/" + name + ".frag");
}

Shader::~Shader()
{
  if (active == this)
    active = nullptr;
  glUseProgram(0);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glDeleteProgram(program);
}

void Shader::load(const std::string& sname, const std::string& vfname, const std::string& ffname)
{
  name = sname;

  GLint success = 0;
  vertex = compile(GL_VERTEX_SHADER, readFile(vfname.c_str()).c_str(), vfname);
  fragment = compile(GL_FRAGMENT_SHADER, readFile(ffname.c_str()).c_str(), ffname);
  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);

  // check for errors
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    std::stringstream ss;
    ss << "Failed to link shaders:" << std::endl;
    ss << infoLogProgram(program) << std::endl;
    std::cerr << ss.str() << std::endl;
    throw ss.str();
  }
}

void Shader::activate() const
{
  glUseProgram(program);

  active = const_cast<Shader*>(this);
}

void Shader::update() const
{
  if (this != active)
    activate();
  GLint uniView = glGetUniformLocation(handle(), "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera.getView()));

  GLint uniProj = glGetUniformLocation(handle(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(camera.getProjection(static_cast<float>(screenWidth), static_cast<float>(screenHeight))));

  GLint uniCam = glGetUniformLocation(handle(), "camera");
  if (uniCam >= 0)
    glUniform3fv(uniCam, 1, glm::value_ptr(camera.getPosition()));

  GLint uniGamma = glGetUniformLocation(handle(), "gamma");
  if (uniGamma >= 0)
    glUniform1f(uniGamma, 1.0);
}

void Shader::setLighting() const
{
  GLint loc = glGetUniformLocation(handle(), "lPosition");
  assert(loc >= 0);
  glUniform3fv(loc, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

  loc = glGetUniformLocation(handle(), "lColour");
  assert(loc >= 0);
  glUniform3fv(loc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

  loc = glGetUniformLocation(handle(), "lAmbientCoefficient");
  assert(loc >= 0);
  glUniform1f(loc, 0.01f);

  loc = glGetUniformLocation(handle(), "lAttenuation");
  assert(loc >= 0);
  glUniform1f(loc, 0.00001f);
}

Shader* Shader::getActive()
{
  return active;
}

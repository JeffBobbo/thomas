#include <gui/gui.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <../src/internal.h>
#include <event.h>
#include <receiver.h>
#include <shader.h>
#include <texturemanager.h>
#include <engine.h>

#include <gui/label.h>

namespace engine
{
gui::Window* node = nullptr;
gui::Element* focus = nullptr;

gui::Window* gui::root()
{
  return node;
}

gui::Element* gui::focused()
{
  return focus;
}

void gui::init()
{
  gui::Label::init();
  node = new gui::Window();
  node->position = glm::ivec4(0, 0, 0, 0);
  node->relative = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
  node->setColour(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void gui::idle()
{
  if (!node)
    return;
  node->idle();
}

void gui::draw()
{
  if (!node)
    return;
  const engine::Program* program = engine::ProgramManager::get("gui");
  program->activate();

  glm::mat4 view = glm::mat4(1.0f);
  GLint uniView = glGetUniformLocation(program->handle(), "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, 0.0f, 100.0f);
  GLint uniProj = glGetUniformLocation(program->handle(), "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glActiveTexture(GL_TEXTURE0);
  node->draw();
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}

void gui::close()
{
  delete node;
  gui::Label::terminate();
}

void gui::onEvent(const Event& e)
{
  bool r = focus ? focus->onEvent(e) : false;
  if (!r)
    r = node->onEvent(e);
  if (!r)
    receiver->onEvent(e);
}
}

#include "gui.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../internal.h"
#include "../event.h"
#include "../receiver.h"
#include "../shader.h"
#include "../texturemanager.h"
#include "../../engine.h"

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

#include <iostream>
class HWindow : public gui::Window
{
  virtual bool onEvent(const Event& e) override
  {
    switch (e.type)
    {
      case Event::Type::GUI:
      {
        if (e.gui.type == Event::GUIType::ELEMENT_ENTER)
        {
          setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
          std::cout << "going in" << std::endl;
        }
        else if (e.gui.type == Event::GUIType::ELEMENT_LEAVE)
        {
          setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
          std::cout << "going out" << std::endl;
        }
        return true;
      }
      break;
      default:
      break;
    }
    return false;
  }
};

void gui::init()
{
  node = new gui::Window();
  node->position = glm::ivec4(0, 0, 0, 0);
  node->relative = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
  node->setColour(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

  HWindow* right = new HWindow();
  right->position = glm::ivec4(120, 120, 160, 240);
  right->relative = glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
  right->setColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  node->add(right);

  gui::Window* sub = new gui::Window();
  sub->position = glm::ivec4(0, 0, 150, 74);
  sub->relative = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  sub->setImage(TextureManager::getTexture("img/ui/barframe.png"));
  node->add(sub);
}

void gui::update()
{
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
}

void gui::onEvent(const Event& e)
{
  bool r = focus ? focus->onEvent(e) : false;
  if (!r)
    receiver->onEvent(e);
}

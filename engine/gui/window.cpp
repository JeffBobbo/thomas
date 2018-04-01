#include "window.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"

namespace gui
{
  Window::Window()
  : Element()
  , colour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
  , texture(-1)
  {
  }

  Window::~Window()
  {
    removeChildren();
  }

  void Window::idle()
  {
    for (auto& it : children)
      it->idle();
  }

  void Window::draw() const
  {
    if (!isVisible())
      return;

    static GLuint vao = 0;
    if (vao == 0)
    {
      float quad[] = {
        //  x,     y,    z,    t,    s
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
      };

      GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
      };
      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);

      GLuint vbo;
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

      GLuint ebo;
      glGenBuffers(1, &ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

      const engine::Program* program = engine::ProgramManager::get("gui");
      GLint posAttrib = glGetAttribLocation(program->handle(), "in_vertex");
      glEnableVertexAttribArray(posAttrib);
      glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

      GLint uvAttrib = glGetAttribLocation(program->handle(), "in_uv");
      glEnableVertexAttribArray(uvAttrib);
      glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    }

    glBindVertexArray(vao);
    const engine::Program* program = engine::Program::active();

    glm::mat4 model = glm::mat4(1.0f);
    glm::ivec2 pos, size;
    getRect(pos, size);
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    // model = glm::rotate(model, ?);
    model = glm::scale(model, glm::vec3(size, 0.0f));
    GLint uniModel = glGetUniformLocation(program->handle(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    if (texture >= 0)
    {
      GLint uniDiffuse = glGetUniformLocation(program->handle(), "diffuse");
      glUniform1i(uniDiffuse, 0);
      glBindTexture(GL_TEXTURE_2D, texture);
    }
    glUniform1i(glGetUniformLocation(program->handle(), "hasTexture"), texture >= 0);

    GLint uniColour = glGetUniformLocation(program->handle(), "colour");
    glUniform4fv(uniColour, 1, glm::value_ptr(colour));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (auto& it : children)
      it->draw();
  }
}

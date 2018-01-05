#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../shader.h"

const size_t STACK_SIZE = 8;

class Matrix
{
  static Matrix matrix;
  Matrix()
  {
    stack = new glm::mat4[STACK_SIZE];
    capacity = STACK_SIZE;
    level = 0;
  }
public:
  ~Matrix()
  {
    delete[] stack;
  }

  static inline void push()
  {
    assert(matrix.level+1 < matrix.capacity);
    ++matrix.level;
    matrix.stack[matrix.level] = matrix.stack[matrix.level-1];
  }
  static inline void pop()
  {
    assert(matrix.level > 0);
    --matrix.level;
  }
  static inline void reset()
  {
    matrix.level = 0;
    matrix.stack[0] = glm::mat4(1.0f);
  }

  static inline void set(const glm::mat4& m)
  {
    matrix.stack[matrix.level] = m;
  }

  static inline const glm::mat4& get()
  {
    return matrix.stack[matrix.level];
  }

  static inline void rotate(const float radians, const glm::vec3& axis)
  {
    matrix.stack[matrix.level] = glm::rotate(matrix.stack[matrix.level], radians, axis);
  }

  static inline void translate(const glm::vec3& by)
  {
    matrix.stack[matrix.level] = glm::translate(matrix.stack[matrix.level], by);
  }

  static inline void scale(const glm::vec3& by)
  {
    matrix.stack[matrix.level] = glm::scale(matrix.stack[matrix.level], by);
  }

  static inline void scale(const float& by)
  {
    matrix.stack[matrix.level] = glm::scale(matrix.stack[matrix.level], glm::vec3(by));
  }

  static inline void apply()
  {
    GLint uniform = glGetUniformLocation(engine::Program::active()->handle(), "model");
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix.stack[matrix.level]));
  }

  static void print();

private:
  glm::mat4* stack;
  size_t level;
  size_t capacity;
};

#endif

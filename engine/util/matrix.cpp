#include "matrix.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

Matrix Matrix::matrix;

void Matrix::print()
{
  const auto& m = matrix.stack[matrix.level];
  std::cout << glm::to_string(m);
}

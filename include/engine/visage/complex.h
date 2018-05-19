#ifndef VISAGECOMPLEX_H_INCLUDE
#define VISAGECOMPLEX_H_INCLUDE

#include "visage.h"

#include <vector>

#include "../util/matrix.h"

class VisageComplex: public Visage
{
public:
  VisageComplex() {}
  virtual ~VisageComplex()
  {
    for (Visage* v : visages)
      delete v;
  }

  virtual inline Type type() const { return Type::COMPLEX; }
  inline void add(Visage* const v) { visages.push_back(v); }

  virtual void draw()
  {
    for (Visage* const v : visages)
    {
      Matrix::push();
      v->draw();
      Matrix::pop();
    }
  }

private:
  std::vector<Visage* > visages;
};

#endif

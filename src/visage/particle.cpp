#include <visage/particle.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/random.hpp>

#include <engine.h>
#include <shader.h>
#include <texturemanager.h>
#include <object/camera.h>
#include <util/random.h>
#include <util/util.h>

ParticleSystem::ParticleSystem()
  : max(1)
  , quad_vao(0), quad_vbo(0), quad_ebo(0), texture(0)
  , interval(1000)
  , lifeMin(9000), lifeMax(10000)
  , sizeStart(10.0f), sizeEnd(10.0f)
  , speedStart(1.0f), speedEnd(1.0f)
  , c0(1.0, 1.0, 0.0, 0.0), c1(1.0, 1.0, 1.0, 0.0)
{
  particles = new Particle[max];
  last = particles;
  end = particles + max;
}

ParticleSystem::~ParticleSystem()
{
  if (particles)
    delete[] particles;

  if (quad_vao)
    glDeleteBuffers(1, &quad_vao);
  if (quad_vbo)
    glDeleteBuffers(1, &quad_vbo);
  if (quad_ebo)
    glDeleteBuffers(1, &quad_ebo);
  if (texture)
    glDeleteTextures(1, &texture);
}

void ParticleSystem::add(int n)
{
  if (!quad_vao)
  {
    float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    GLuint elements[] = {
      0, 1, 2,
      2, 3, 0
    };
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &quad_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    const engine::Program* program = engine::ProgramManager::get("particle");
    GLint posAttrib = glGetAttribLocation(program->handle(), "in_vertex");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    GLint texAttrib = glGetAttribLocation(program->handle(), "in_uv");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
  }
  // texture
  if (!texture)
  {
    texture = TextureManager::getTexture("img/particles/particle_soft.png");
  }

  for (int i = 0; i < n && !full(); ++i)
  {
    *last = Particle();
    last->pos = glm::vec3(0.0f);
    last->vel = glm::vec3(random(-speedStart, speedStart), random(-speedStart, speedStart), random(-speedStart, speedStart));
    last->size = sizeStart;
    last->lifespan = lifeMax == 0 ? lifeMin : random(lifeMin, lifeMax);
    ++last;
  }
}

void ParticleSystem::erase(Particle* p)
{
  if (!empty())
    *p = *(--last);
}

void ParticleSystem::update()
{
  for (Particle* p = particles; p < last; ++p)
  {
    p->age += delta();
    if (p->age < p->lifespan)
    {
      double progress = p->age / static_cast<double>(p->lifespan);

      ARGB colour = c0.interpolate(c1, progress);
      p->col = glm::vec4(colour.r, colour.g, colour.b, colour.a);

      p->pos += p->vel * (delta() / 1000.0f);

      p->size = lerp(sizeStart, sizeEnd, progress);
    }
    else
    {
      erase(p);
    }
  }

  if (interval.isTime())
  {
    int n = interval.ticks();
    add(n);
    interval.advance(n);
  }
}

//#include <iostream>
void ParticleSystem::draw()
{
  // update the particles
  update();

  Visage::draw();

  // disable and enable stuff
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBindVertexArray(quad_vao);

  const engine::Program* program = engine::ProgramManager::get("particle");
  program->activate();
  program->update();
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(program->handle(), "diffuse"), 0);
  glBindTexture(GL_TEXTURE_2D, texture);
  GLint uniModel = glGetUniformLocation(program->handle(), "model");
  GLint uniColor = glGetUniformLocation(program->handle(), "colourMult");
  for (Particle* p = particles; p != last; ++p)
  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), p->pos);
    //model = glm::translate(model, camera.getPosition());
    //std::cout << model[3][0] << " " << model[3][1] << " " << model[3][2] << std::endl;
    model = glm::scale(model, glm::vec3(p->size));
    /*
    model[0][0] = 1.0f;
    model[0][1] = 0.0f;
    model[0][2] = 0.0f;
    model[1][0] = 0.0f;
    model[1][1] = 1.0f;
    model[1][2] = 0.0f;
    model[2][0] = 0.0f;
    model[2][1] = 0.0f;
    model[2][1] = 1.0f;
    GLint uniView = glGetUniformLocation(Program::getActive()->handle(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    */
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(uniColor, p->col.r, p->col.g, p->col.b, p->col.a);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDisable(GL_BLEND);
}

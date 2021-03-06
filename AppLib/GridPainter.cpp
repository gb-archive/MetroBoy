#include "AppLib/GridPainter.h"
#include "AppLib/GLBase.h"

#include <stdio.h>
#include <math.h>
#include "SDL/include/SDL.h"
#include "glad/glad.h"

//-----------------------------------------------------------------------------

static const GLchar* grid_glsl = R"(

struct Rect {
  float x;
  float y;
  float w;
  float h;
};

layout(std140) uniform GridUniforms
{
  Rect viewport;
};

#ifdef _VERTEX_

layout(location = 0) in  vec2 vert_pos;
out vec2 world_pos; // interpolating this is going to lose precision...

void main() {
  world_pos.x = vert_pos.x * viewport.w + viewport.x;
  world_pos.y = vert_pos.y * viewport.h + viewport.y;

  gl_Position = vec4(2.0 * vert_pos.x - 1.0, -2.0 * vert_pos.y + 1.0, 1.0, 1.0);
}

#endif

#ifdef _FRAGMENT_

in  vec2 world_pos;
out vec4 frag_col;

void main() {
  if (world_pos.x < -32768.0 ||
      world_pos.x >  32768.0 ||
      world_pos.y < -32768.0 ||
      world_pos.y >  32768.0) {
    frag_col = vec4(0.4, 0.0, 0.0, 1.0);
    return;
  }

  bool bx = fract(world_pos.x * (1.0 / 64.0)) > 0.5;
  bool by = fract(world_pos.y * (1.0 / 64.0)) > 0.5;
  bool b = bx ^^ by;

  float ga = 14.0 / 255.0;
  float gb = 19.0 / 255.0;

  frag_col.r = b ? ga : gb;
  frag_col.g = b ? ga : gb;
  frag_col.b = b ? ga : gb;
  frag_col.a = 1.0;
}

#endif

)";

//-----------------------------------------------------------------------------

void GridPainter::init() {
  grid_prog = create_shader("grid_glsl", grid_glsl);

  float quad[] = {
     0,  0,  1,  0,  1,  1,
     0,  0,  1,  1,  0,  1,
  };

  grid_vao = create_vao();
  grid_vbo = create_vbo(sizeof(quad), quad);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  grid_ubo = create_ubo(sizeof(GridUniforms));
}

//-----------------------------------------------------------------------------

#pragma warning(disable:4189)

void GridPainter::render(Viewport view) {
  bind_shader(grid_prog);

  grid_uniforms.viewport = {(float)view.mx(), (float)view.my(), (float)view.dx(), (float)view.dy() };
  update_ubo(grid_ubo, sizeof(grid_uniforms), &grid_uniforms);
  bind_ubo(grid_prog, "GridUniforms", 0, grid_ubo);

  bind_vao(grid_vao);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

//-----------------------------------------------------------------------------

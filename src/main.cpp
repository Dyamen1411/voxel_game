#include <stdio.h>

#include <GLES3/gl32.h>

#include "model.h"
#include "shader.h"
#include "utils.h"
#include "window.h"

#include "shader.h"

int main (int argc, char ** argv) {
  Window window;
  window.create(1600, 900, "Hello World!");

	b32 running = 1;
	b32 fullscreen = 0;
  
  GLfloat vertices[] = {
    -.5f, -.5f,
     .5f, -.5f,
     .5f,  .5f,
    -.5f,  .5f,
  };

  GLfloat colors[] = {
    0.f, 0.f, 1.f,
    1.f, 0.f, 1.f,
    1.f, 1.f, 1.f,
    0.f, 1.f, 1.f,
  };

  GLuint indices[] = {
    0, 2, 3,
    0, 1, 2,
  };
  
  Model model;
  model.setVertices(vertices, 4);
  model.setColors(colors, 4);
  model.setIndices(indices, 6);

  Shader shader("", "");

/*  Model model = {
    vertices,
    indices,
    4,
    6,
  };

  GLuint vao;
  GLuint vbo;
  GLuint ibo;
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, 2 * model.vertices_count * sizeof(GLfloat), model.vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices_count * sizeof(GLuint), model.indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);*/

	while (running) {
		SDL_Event event;
		while (window.pollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = 0;
						break;

					case 'f':
						fullscreen ^= 1;
            window.setFullscreen(fullscreen);
						break;

					default:
						break;
				}
			}
			else if (event.type == SDL_QUIT) {
				running = 0;
			}
		}

		glViewport(0, 0, 1600, 900);
		glClearColor(1.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT);

/*    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);*/
    
    model.bind();
    glDrawElements(GL_TRIANGLES, model.getIndicesCount(), GL_UNSIGNED_INT, 0);
    model.unbind();

//    glDisableVertexAttribArray(0);
    
    window.update();
	}
  
/*  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);
  glDeleteVertexArrays(1, &vao);*/

	return 0;
}

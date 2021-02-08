#include "model.h"

#include <GLES3/gl32.h>

Model::Model() {
  glGenVertexArrays(1, &m_vaoId);
  glGenBuffers(3, m_vboIds);
}

Model::~Model() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteVertexArrays(1, &m_vaoId);
  glDeleteBuffers(3, m_vboIds);
}

void Model::setVertices(GLfloat * vertices, GLuint vertices_count) {
  m_vertices = vertices;
  m_vertices_count = vertices_count;

  glBindVertexArray(m_vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);

  glBufferData(GL_ARRAY_BUFFER, 2 * m_vertices_count * sizeof(GLfloat), m_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
void Model::setColors(GLfloat * colors, GLuint colors_count) {
  m_colors = colors;
  m_colors_count = colors_count;

  glBindVertexArray(m_vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);

  glBufferData(GL_ARRAY_BUFFER, 3 * m_colors_count * sizeof(GLfloat), m_colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Model::setIndices(GLuint * indices, GLuint indices_count) {
  m_indices = indices;
  m_indices_count = indices_count;
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_count * sizeof(GLuint), m_indices, GL_STATIC_DRAW);
  glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void Model::bind() const {
  glBindVertexArray(m_vaoId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[2]);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void Model::unbind() const {
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

GLuint Model::getIndicesCount() const {
  return m_indices_count;
}


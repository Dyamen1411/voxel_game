#ifndef SHADER_BASE_H
#define SHADER_BASE_H

#include <fstream>
#include <sstream>
#include <iostream>

#include <GLES3/gl32.h>
#include <map>
#include <string>

class Shader {
  public:
    Shader(const char * vert_path, const char * frag_path);
//    ~Shader();

  public:
    void bind() const;
    void unbind() const;

  protected:
    void mapAttrib(const char * name);
    int getAttribLoc(const char * name) const;

    void setFloat(const char * name, float value);

  private:
    GLuint m_program;
    std::map<const char *, int> m_attribs;
};

size_t _strlen(const char * a) {
  size_t i = 0;
  while (*(a+i) != '\0') {
    ++i;
  }
  return i;
}

int _strcmp(const char * a, const char * b) {
  size_t al = _strlen(a);
  size_t bl = _strlen(b);
  
  if (al != bl) {
    return 0;
  }

  for (size_t i = 0; i < al; ++i) {
    if (*(a+i) != *(b+i)) {
      return 0;
    }
  }

  return 1;
}

Shader::Shader(const char * vert_path, const char * frag_path) {

  const char * a = "abc";
  const char * b = "abc";
  const char * c = "cba";

  printf("%c\n", _strcmp(a, b) ? 'y' : 'n');
  printf("%c\n", _strcmp(a, c) ? 'y' : 'n');

  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;

  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  try {
    // open files
    v_shader_file.open(vert_path);
    f_shader_file.open(frag_path);
    std::stringstream v_shader_stream, f_shader_stream;
    // read file's buffer contents into streams
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();		
    // close file handlers
    v_shader_file.close();
    f_shader_file.close();
    // convert stream into string
    vertex_code   = v_shader_stream.str();
    fragment_code = f_shader_stream.str();		
  } catch(std::ifstream::failure e) {
      printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
  }
  
  // 2. Compile shaders
  const char* v_shader_code = vertex_code.c_str();
  const char* f_shader_code = fragment_code.c_str();
  
  unsigned int vertex;
  unsigned int fragment;
  int success;
  char info_log[512];
  
  // Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &v_shader_code, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
  }

  // Fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &f_shader_code, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
  }

  // Shader program
  m_program = glCreateProgram();
  glAttachShader(m_program, vertex);
  glAttachShader(m_program, fragment);
  glLinkProgram(m_program);
  
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_program, 512, NULL, info_log);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

/*Shader::~Shader() {
  printf("end\n");
}*/

void Shader::bind() const {
  glUseProgram(m_program);
}

void Shader::unbind() const {
  glUseProgram(0);
}

void Shader::mapAttrib(const char * name) {
  std::map<const char *, int>::iterator i = m_attribs.find(name);
  if (i == m_attribs.end()) {
    int _loc = glGetAttribLocation(m_program, name);
    m_attribs[name] = _loc;
  } else {
    printf("WARNING: Attrib \"%s\" is already defined in shader %d!\n", name, m_program);
  }
}

int Shader::getAttribLoc(const char * name) const {
/*  std::map<const char *, int>::iterator i = m_attribs.find(name);
   if (i != m_attribs.end()) {
     return m_attribs[name]; 
   } else {
    printf("ERROR: Attrib \"%s\" is not registered in shader %d!\n", name, m_program);
    return -1;
   }*/
  return 0;
}

void Shader::setFloat(const char * name, float value) {
  
}

#endif /* SHADER_BASE_H */

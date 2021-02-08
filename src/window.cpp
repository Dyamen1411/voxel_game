#include "utils.h"
#include "window.h"

Window::Window() {
}

Window::~Window() {
  SDL_GL_DeleteContext(m_context);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Window::create(int width, int height, const char * title) {
  m_width = width;
  m_height = height;
  m_window = SDL_CreateWindow(title, 0, 0, m_width, m_height, SDL_WINDOW_OPENGL);
  m_context = SDL_GL_CreateContext(m_window);
}

void Window::update() {
  SDL_GL_SwapWindow(m_window);
}

void Window::setFullscreen(int fullscreen) {
  if (fullscreen) {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	} else {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_OPENGL);
	}
}

int Window::pollEvent(SDL_Event * event) {
  return SDL_PollEvent(event);
}


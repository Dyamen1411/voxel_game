#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "utils.h"

class Window {
  public:
    Window();
    ~Window();

  public:
    void create(int width, int height, const char * title);
    void update();
    void setFullscreen(b32 fullscreen);

    int pollEvent(SDL_Event * event);

  private:
    SDL_Window * m_window;
    SDL_GLContext m_context;

    int m_width;
    int m_height;
};

#endif /* WINDOW_H */

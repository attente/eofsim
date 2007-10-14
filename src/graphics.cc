#include "graphics.hh"
#include "sdl.hh"
#include "scene.hh"

#include <iostream>

static scene *sim;

int graphics_initialise() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        std::cerr << "SDL subsystems could not be initialized.\n";
        return 1;
    }

    SDL_WM_SetCaption("flight", "flight");
    const int width(800), height(600);

    if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE,          8) ||
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,        8) ||
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,         8) ||
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,        8) ||
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,      1) ||
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,      32) ||
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,       24) ||
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,      0) ||
        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    0) ||
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  0) ||
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   0) ||
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  0) ||
        SDL_SetVideoMode(width, height, 0, SDL_OPENGL) == NULL) {
            std::cerr << "Appropriate OpenGL attributes could not be set.\n";
            SDL_Quit();
            return 2;
    }

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.7, 0.9, 1.0, 1.0);
    GLfloat bright[] = { 1, 1, 1, 1 };
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, bright);

    sim = new scene();
    return 0;
}

void graphics_destroy() {
    delete sim;

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    SDL_Quit();
}

void graphics_render() {
    sim->render();
}

void graphics_stop() {
    sim->stop();
}

bool graphics_loop() {
    return sim->loop();
}

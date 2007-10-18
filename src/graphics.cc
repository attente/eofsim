#include "graphics.h"
#include "physics.h"
#include "sdl.hh"
#include "font.hh"
#include "scene.hh"
#include "texture.hh"

#include <iostream>

static GLuint list;
static font *glyph;
static scene *sim;

int graphics_initialise() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL subsystems could not be initialized.\n";
        return 1;
    }

    int width(800), height(600);
    SDL_WM_SetCaption("flight", "flight");
    const int flags(SDL_OPENGL | SDL_FULLSCREEN);
    SDL_Rect **modes(SDL_ListModes(NULL, flags));

    if (modes != NULL && modes != reinterpret_cast< SDL_Rect ** >(-1)) {
        width = modes[0]->w;
        height = modes[0]->h;
    }

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
        SDL_SetVideoMode(width, height, 0, flags) == NULL) {
            std::cerr << "Appropriate OpenGL attributes could not be set.\n";
            SDL_Quit();
            return 2;
    }

    glEnable(GL_BLEND);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.7, 0.9, 1.0, 1.0);
    GLfloat params[] = { 1, 1, 1, 1 };
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, params);

    params[0] = 0.20;
    params[1] = 0.20;
    params[2] = 0.20;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_AMBIENT, params);
    params[0] = 0.50;
    params[1] = 0.50;
    params[2] = 0.50;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, params);
    params[0] = 0.60;
    params[1] = 0.60;
    params[2] = 0.60;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_SPECULAR, params);
    params[0] = 1.00;
    params[1] = 3.00;
    params[2] = 2.00;
    params[3] = 0.00;
    glLightfv(GL_LIGHT0, GL_POSITION, params);

    glyph = new font("../data/font.fnt");
    sim = new scene();
    list = glGenLists(1);

    glNewList(list, GL_COMPILE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 600, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4d(0, 0, 0, 0.60);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(15, 90);
    glVertex2d(60, 90);
    glVertex2d(15, 510);
    glVertex2d(60, 510);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor4d(1, 0, 0, 0.60);
    glVertex2d(30, 100);
    glVertex2d(35, 100);
    glColor4d(1, 1, 0, 0.60);
    glVertex2d(30, 150);
    glVertex2d(35, 150);
    glColor4d(0, 1, 0, 0.60);
    glVertex2d(30, 299);
    glVertex2d(35, 299);
    glColor4d(0, 0, 1, 0.60);
    glVertex2d(30, 301);
    glVertex2d(35, 301);
    glColor4d(0, 1, 1, 0.60);
    glVertex2d(30, 500);
    glVertex2d(35, 500);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor4d(1, 0, 1, 0.60);
    glVertex2d(40, 100);
    glVertex2d(45, 100);
    glColor4d(0, 0, 1, 0.60);
    glVertex2d(40, 300);
    glVertex2d(45, 300);
    glColor4d(1, 0, 1, 0.60);
    glVertex2d(40, 500);
    glVertex2d(45, 500);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(100, 30);
    glVertex2d(100, 35);
    glVertex2d(197, 30);
    glVertex2d(197, 35);
    glColor4d(1, 1, 1, 0.60);
    glVertex2d(198, 30);
    glVertex2d(198, 35);
    glVertex2d(202, 30);
    glVertex2d(202, 35);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(203, 30);
    glVertex2d(203, 35);
    glVertex2d(597, 30);
    glVertex2d(597, 35);
    glColor4d(1, 1, 1, 0.60);
    glVertex2d(598, 30);
    glVertex2d(598, 35);
    glVertex2d(602, 30);
    glVertex2d(602, 35);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(603, 30);
    glVertex2d(603, 35);
    glVertex2d(700, 30);
    glVertex2d(700, 35);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(765, 100);
    glVertex2d(770, 100);
    glVertex2d(765, 197);
    glVertex2d(770, 197);
    glColor4d(1, 1, 1, 0.60);
    glVertex2d(765, 198);
    glVertex2d(770, 198);
    glVertex2d(765, 202);
    glVertex2d(770, 202);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(765, 203);
    glVertex2d(770, 203);
    glVertex2d(765, 497);
    glVertex2d(770, 497);
    glColor4d(1, 1, 1, 0.60);
    glVertex2d(765, 498);
    glVertex2d(770, 498);
    glVertex2d(765, 500);
    glVertex2d(770, 500);
    glEnd();

    glEndList();

    return 0;
}

void graphics_destroy() {
    delete glyph;
    delete sim;

    glDeleteLists(list, 1);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHT0);
    glDisable(GL_BLEND);
    SDL_Quit();
}

void graphics_render() {
    sim->render();

    glCallList(list);

    double thrust(300 - physics_get_thrust() * 25);
    glColor4d(1, 0, 0, 0.60);
    glBegin(GL_TRIANGLES);
    glVertex2d(20, thrust - 5);
    glVertex2d(30, thrust);
    glVertex2d(20, thrust + 5);

    double flaps(300 - physics_get_flaps() * 25);
    glColor4d(1, 0, 1, 0.60);
    glVertex2d(55, flaps - 5);
    glVertex2d(45, flaps);
    glVertex2d(55, flaps + 5);

    double x, y;
    physics_get_location(&x, &y);

    x = 600 - x / 25;
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(x - 5, 20);
    glVertex2d(x, 30);
    glVertex2d(x + 5, 20);

    y = 500 - 3 * y / 10;
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(780, y - 5);
    glVertex2d(770, y);
    glVertex2d(780, y + 5);
    glEnd();

    SDL_GL_SwapBuffers();
}

void graphics_stop() {
    sim->stop();
}

bool graphics_loop() {
    return sim->loop();
}

void graphics_print(const char *s, double x, double y,
                         double c, double h, double v) {
    glyph->print(s, x, y, c, h, v);
}

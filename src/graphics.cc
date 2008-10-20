/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "graphics.h"
#include "physics.h"
#include "sdl.hh"
#include "font.hh"
#include "scene.hh"
#include "texture.hh"
#include "particle.hh"

#include <iostream>

static GLuint list;
static font *glyph;
static font *white;
static scene *sim;
static int mode;

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

    glEnable (GL_BLEND);
    glEnable (GL_LIGHT0);
    glEnable (GL_TEXTURE_2D);
    // glEnable (GL_LINE_SMOOTH);
    // glEnable (GL_POINT_SMOOTH);
    // glEnable (GL_POLYGON_SMOOTH);

    glClearColor(0.7, 0.9, 1.0, 1.0);
    GLfloat params[] = { 1, 1, 1, 1 };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, params);

    // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    // glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    params[0] = 0.30;
    params[1] = 0.30;
    params[2] = 0.30;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_AMBIENT, params);
    params[0] = 0.60;
    params[1] = 0.60;
    params[2] = 0.60;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, params);
    params[0] = 0.80;
    params[1] = 0.80;
    params[2] = 0.80;
    params[3] = 1.00;
    glLightfv(GL_LIGHT0, GL_SPECULAR, params);

    particle_init ();

    glyph = new font("../data/font.fnt");
    white = new font("../data/whitefont.fnt");

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

    glBegin (GL_TRIANGLE_STRIP);
    glColor4d (0, 0, 0, 0.60);
    glVertex2d (100, 30);
    glVertex2d (100, 35);

    for (int i = 0; i < 8; i++)
      {
        double x = 200 + 400.0 * i / 7;

        glVertex2d (x - 3, 30);
        glVertex2d (x - 3, 35);
        glColor4d (1, 1, 1, 0.60);
        glVertex2d (x - 2, 30);
        glVertex2d (x - 2, 35);
        glVertex2d (x + 2, 30);
        glVertex2d (x + 2, 35);
        glColor4d (0, 0, 0, 0.60);
        glVertex2d (x + 3, 30);
        glVertex2d (x + 3, 35);
      }

    glVertex2d (700, 30);
    glVertex2d (700, 35);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor4d(0, 0, 0, 0.60);
    glVertex2d(765, 100);
    glVertex2d(770, 100);
    glVertex2d(765, 497);
    glVertex2d(770, 497);
    glColor4d(1, 1, 1, 0.60);
    glVertex2d(765, 498);
    glVertex2d(770, 498);
    glVertex2d(765, 500);
    glVertex2d(770, 500);
    glEnd();

    glEndList();
    mode = 0;
    return 0;
}

void graphics_destroy() {
    delete white;
    delete glyph;
    delete sim;

    particle_exit ();

    glDeleteLists(list, 1);

    // glDisable (GL_POLYGON_SMOOTH);
    // glDisable (GL_POINT_SMOOTH);
    // glDisable (GL_LINE_SMOOTH);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_LIGHT0);
    glDisable (GL_BLEND);

    SDL_Quit();
}

void
graphics_render (double white,
                 double sepia)
{
    char buffer[80];

    sim->render(mode);

    if (mode != 2)
      {
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
        x = 600 - (x - 1000.0) / 7000 * 400;

        if (x >= 100 && x <= 700)
          {
            glColor4d(0, 0, 0, 0.60);
            glVertex2d(x - 5, 20);
            glVertex2d(x, 30);
            glVertex2d(x + 5, 20);
          }

        y = 500 - y * 400.0 / 1500;
        glColor4d(0, 0, 0, 0.60);
        glVertex2d(780, y - 5);
        glVertex2d(770, y);
        glVertex2d(780, y + 5);
        glEnd();

        y = physics_get_next_ring ();
        y = 500 - y * 400.0 / 1500;
        glBegin (GL_TRIANGLE_STRIP);
        glColor4d (1, 1, 1, 0.60);
        glVertex2d (765, y - 32);
        glVertex2d (770, y - 32);
        glVertex2d (765, y - 3);
        glVertex2d (770, y - 3);
        glColor4d (1, 1, 1, 1);
        glVertex2d (765, y - 2);
        glVertex2d (770, y - 2);
        glVertex2d (765, y + 2);
        glVertex2d (770, y + 2);
        glColor4d (1, 1, 1, 0.60);
        glVertex2d (765, y + 3);
        glVertex2d (770, y + 3);
        glVertex2d (765, y + 32);
        glVertex2d (770, y + 32);
        glEnd ();
      }
    else
      {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 800, 600, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      }

    if (mode == 2)
      {
        graphics_print ("Score:", 100, 30, 2, 0, 0);
        sprintf (buffer, "%.1lf", physics_get_score());
        graphics_print (buffer, 700, 30, 2, 1, 0);

        if (physics_get_time_bonus () != 0)
          {
            sprintf (buffer, "+%.1lf Time Bonus", physics_get_time_bonus ());
            graphics_print (buffer, 400, 100, 2, 0.5, 0);
          }

        graphics_print ("Time:", 100, 500, 2, 0, 1);
        sprintf (buffer, "%.1lf s", physics_get_time ());
        graphics_print (buffer, 700, 500, 2, 1, 1);
      }
    else
      {
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (-1, 1, -1, 1);

        glMatrixMode (GL_MODELVIEW);
        glPushMatrix ();
        glLoadIdentity ();

        glBindTexture (GL_TEXTURE_2D, 0);

        glBegin (GL_TRIANGLE_STRIP);
        glColor4d (0.75, 0.6, 0.3, sepia);
        glVertex2d (-1, -1);
        glVertex2d (-1,  1);
        glVertex2d ( 1, -1);
        glVertex2d ( 1,  1);
        glEnd ();

        glBegin (GL_TRIANGLE_STRIP);
        glColor4d (1, 1, 1, white);
        glVertex2d (-1, -1);
        glVertex2d (-1,  1);
        glVertex2d ( 1, -1);
        glVertex2d ( 1,  1);
        glEnd ();

        glPopMatrix ();

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (0, 800, 600, 0);
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();

        graphics_print(physics_get_message(), 400, 500, 2, 0.5, 1);
      }

    SDL_GL_SwapBuffers ();
}

void graphics_mode(int m) {
    mode = m;
}

int graphics_get_mode (void)
{
  return mode;
}

void graphics_stop() {
    sim->stop();
}

bool graphics_loop() {
    return sim->loop();
}

void graphics_print(const char *s, double x, double y,
                         double c, double h, double v) {
  (mode == 2 ? white : glyph)->print(s, x, y, c, h, v);
}

void graphics_fade ()
{
  const int STEPS = 25;

  for (int i = 0; i < STEPS; i++)
    {
      SDL_Event event;

      if (SDL_PollEvent (&event))
        {
          if (event.type == SDL_QUIT
              || (event.type == SDL_KEYDOWN
                  && event.key.keysym.sym == SDLK_ESCAPE))
            exit (0);

          if (event.type == SDL_KEYDOWN
              && event.key.keysym.sym == SDLK_SPACE)
            return;
        }

      graphics_render (double (STEPS - i - 1) / STEPS, 0.75);

      if (i == STEPS - 1)
        i--;

      SDL_Delay (40);
    }
}

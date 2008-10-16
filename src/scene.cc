/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "scene.hh"
#include "sdl.hh"
#include "camera.hh"
#include "trail.hh"
#include "ring.hh"
#include "physics.h"

#include <vector>
#include <cstdlib>
#include <cmath>

#include <iostream>
using namespace std;

const int size(100), height(1000);
static double f(int i, int j);

scene::scene() : running(true), backdrop ("../data/backdrop.png"),
                 ground("../data/ground.png"), runway("../data/runway.png"),
                 shadow("../data/shadow.png"), stills("../data/static.png"),
                 list(glGenLists(4)), tower("../data/tower.raw"),
                 obj("../data/biplane.raw"), rings (NULL),
                 walkx(0), walky(0) {
    const double limit(4E4);

    glNewList(list, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, ground);

    std::vector< double > z[2];
    z[0].reserve(size + 1);

    for (int i(0); i <= size; i++)
        z[0].push_back(f(0, i));

    for (int i(1); i < size; i++) {
        glBegin(GL_TRIANGLE_STRIP);

        z[1].clear();
        z[1].reserve(size + 1);

        for (int j(0); j <= size; j++)
            z[1].push_back(f(i, j));

        for (int j(0); j <= size; j++) {
            double x(j), y(i - 1);
            x /= size, y /= size;

            if (z[0][j] > height >> 2)
                glColor3d(0.8, 0.6, 0.8);
            else if (z[0][j] > height >> 4)
                glColor3d((1.7 + (rand() % 100) / 50.0) * z[0][j] / height,
                          (0.9 + (rand() % 100) / 50.0) * z[0][j] / height,
                          (1.7 + (rand() % 100) / 50.0) * z[0][j] / height);
            else glColor3d(0, 0, 0);

            glTexCoord2d(x, y);
            x = (x - 0.5) * limit;
            y = (y - 0.5) * limit;
            glVertex3d(x, z[0][j], y);

            x = j, y = i;
            x /= size;
            y /= size;

            if (z[0][j] > height >> 2)
                glColor3d(0.8, 0.6, 0.8);
            else if (z[0][j] > height >> 4)
                glColor3d((1.7 + (rand() % 100) / 50.0) * z[0][j] / height,
                          (0.9 + (rand() % 100) / 50.0) * z[0][j] / height,
                          (1.7 + (rand() % 100) / 50.0) * z[0][j] / height);
            else glColor3d(0, 0, 0);

            glTexCoord2d(x, y);
            x = (x - 0.5) * limit;
            y = (y - 0.5) * limit;
            glVertex3d(x, z[1][j], y);
        }

        z[0] = z[1];
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();

    glNewList(list + 1, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, stills);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex3d(-2E4, 0, -2E4);
    glTexCoord2d(5, 0);
    glVertex3d( 2E4, 0, -2E4);
    glTexCoord2d(0, 5);
    glVertex3d(-2E4, 0,  2E4);
    glTexCoord2d(5, 5);
    glVertex3d( 2E4, 0,  2E4);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();

    glNewList(list + 2, GL_COMPILE);
    glColor3d(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, runway);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex3d(-12.5, 0, -282);
    glTexCoord2d(1, 0);
    glVertex3d( 12.5, 0, -282);
    glTexCoord2d(0, 1);
    glVertex3d(-12.5, 0, 1000);
    glTexCoord2d(1, 1);
    glVertex3d( 12.5, 0, 1000);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();

    glNewList(list + 3, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, shadow);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex3d(-4, 0, -4);
    glTexCoord2d(1, 0);
    glVertex3d( 4, 0, -4);
    glTexCoord2d(0, 1);
    glVertex3d(-4, 0,  4);
    glTexCoord2d(1, 1);
    glVertex3d( 4, 0,  4);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();
}

scene::~scene() {
    glDeleteLists(list, 4);
}

bool scene::loop() const {
    return running;
}

void scene::stop() {
    running = false;
}

void scene::render(int mode) const {
    const double RIGHT = -10;
    const double BACK(15), ABOVE(5);
    const double h(2.00);
    camera view;

    glClearColor(0.7, 0.9, 1.0, 1.0);

    physics_get_location(&view.x.z, &view.x.y);

    if (!mode) {
        double vx(0), vy(0);

        view.x.x += RIGHT;
        view.x.y += ABOVE;
        view.x.z += BACK;
        view.y.x = -RIGHT;
        view.y.y = -ABOVE;
        view.y.z = -BACK;
        view.z.x = -RIGHT;
        view.z.y = 1;
        view.z.z = -BACK;

        if (view.x.y < h)
            view.x.y = h;

        if (physics_is_shaking()) {
            physics_get_direction(&vx, &vy);

            walkx += rand() % 3 - 1;
            walky += rand() % 3 - 1;

            if (walkx < -10) walkx = -10;
            else if (walkx > 10) walky = 10;
            if (walky < -10) walkx = -10;
            else if (walky > 10) walky = 10;

            view.x.x += walkx * vx / 1000;
            view.x.y += walky * vx / 1000;
        }
        else walkx = walky = 0;

        view.position();

        if (physics_is_shaking()) {
            view.x.x -= walkx * vx / 1000;
            view.x.y -= walky * vx / 1000;
        }

        view.x.y -= ABOVE;
        view.x.z -= BACK;

        GLfloat params[] = { -1.0, 5.0, 5.0, 0.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, params);
    }
    else if (mode == 1) {
        view.y.y = view.x.y;
        view.y.z = view.x.z;
        view.x.x = 30;
        view.x.y = 15;
        view.x.z = -60;
        view.y -= view.x;
        view.z.y = 1;
        view.position();

        GLfloat params[] = { -1.0, 5.0, -2.0, 0.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, params);
    }
    else if (mode == 2)
      {
        glClearColor (0, 0, 0, 1);

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        glOrtho (-8000, 8000, -6000, 6000, -10000, 10000);

        view.x.x = 1000;
        view.x.y = 2000;
        view.x.z = 5000;
        view.y.x = -1;
        view.y.y = 0;
        view.y.z = 0;
        view.z.x = 0;
        view.z.y = 1;
        view.z.z = 0;
        view.position ();

        glPushMatrix ();
        glLoadIdentity ();

        glBindTexture (GL_TEXTURE_2D, backdrop);
        glBegin (GL_TRIANGLE_STRIP);
        glColor4d (0, 0, 0, 1);
        glTexCoord2d (0, 1);
        glVertex2d (-8000, -6000);
        glTexCoord2d (0, 0);
        glVertex2d (-8000,  6000);
        glTexCoord2d (1, 1);
        glVertex2d ( 8000, -6000);
        glTexCoord2d (1, 0);
        glVertex2d ( 8000,  6000);
        glEnd ();

        glPopMatrix ();

        GLfloat params[] = { -1.0, 5.0, -2.0, 0.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, params);
      }

    glPushMatrix();
    glTranslated(view.x.x, 0, view.x.z);
    glMatrixMode(GL_TEXTURE);
    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslated(0, view.x.z / 4E4, 0);
    glCallList(list);
    glPopMatrix();
    glColor4d(0, 0, 0, 0.2);
    glPushMatrix();
    glTranslated(0, view.x.z * 5 / 4E4, 0);
    glCallList(list + 1);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glColor4d(0, 0, 0, 1);
    glCallList(list + 2);

    view.x.x = 0;
    physics_get_location(&view.x.z, &view.x.y);

    if (mode != 2 && view.x.y < 100) {
        double s((view.x.y - h) / 100);

        glPushMatrix();
        glColor4d(0, 0, 0, (1 - s) * 0.75);
        glTranslated(view.x.x + 40 * s + 3,
                     0,
                     view.x.z - 20 * s + 3);
        glScaled(s + 1, 1, s + 1);
        glCallList(list + 3);
        glPopMatrix();
    }

    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glTranslated(100, 0, 0);
    glRotated(-90, 1, 0, 0);
    glScaled(2.5, 2.5, 2.5);

    glColor3d(0.90, 0.90, 0.90);
    tower.render();
    glPopMatrix();

    static trail t (1000, view.x.x, view.x.y, view.x.z, 0.5, 0.5, 0.5, 1, 8);
    t.head.x = view.x.x - RIGHT;
    t.head.y = view.x.y - ABOVE;
    t.head.z = view.x.z - BACK;
    t.head.x.a = 100;
    t.head.y.a = 100;
    t.head.z.a = 100;
    t.update (0.1);

    if (mode == 2)
      t.thickness = 8;
    else
      t.thickness = 256;

    t.render ();

    if (rings == NULL || physics_get_serial () != serial)
      {
        delete [] rings;
        serial = physics_get_serial ();
        rings = new ring[physics_get_n_rings ()];

        for (int i = 0; i < physics_get_n_rings (); i++)
          rings[i].set_position (physics_get_rings_horiz ()[i],
                                 physics_get_rings_vert ()[i]);
      }

    for (int i = physics_get_n_rings () - 1; i >= 0; i--)
      {
        rings[i].update (0.1);
        rings[i].render (view.x.z, mode);
      }

    glPushMatrix();
    glTranslated(view.x.x, view.x.y, view.x.z);
    glRotated(physics_get_degrees() - 90, 1, 0, 0);

    if (mode == 1) {
      double factor(std::fabs(view.x.z) / 400);
      glScaled(1 + factor, 1 + factor, 1 + factor);
    }

    glColor3d(0.80, 0, 0);
    obj.render();

    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

static double f(int i, int j) {
    static double h[size][size];
    static bool ready(false);

    if (!ready) {
        for (int m(0); m < size; m++) {
            for (int n(0); n < size; n++)
                h[m][n] = 0;
        }

        for (int m(0); m < size; m++) {
            h[       m][       0] = (height << 2) + rand() % (height << 4);
            h[       m][size - 1] = (height << 2) + rand() % (height << 4);
            h[       0][       m] = (height << 2) + rand() % (height << 4);
            h[size - 1][       m] = (height << 2) + rand() % (height << 4);
        }

        int n(size - 1);
        h[0][0] /= 1 << 6;
        h[0][n] /= 1 << 6;
        h[n][0] /= 1 << 6;
        h[n][n] /= 1 << 6;

        for (int m(0); m < size; m++) {
            for (int r(0); r < size; r++) {
                for (int c(0); c < size; c++) {
                    double avg(0);
                    int count(0);

                    for (int y(r - 1); y < r + 2 && y < size; y++) {
                        if (y < 0) continue;

                        for (int x(c - 1); x < c + 2 && x < size; x++) {
                            if (x < 0) continue;
                            avg += h[y][x];
                            count++;
                        }
                    }

                    h[r][c] = avg / count;
                }
            }
        }

        ready = true;
    }

    return h[i][j];
}

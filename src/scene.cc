#include "scene.hh"
#include "sdl.hh"
#include "camera.hh"
#include "physics.hh"

#include <vector>

const int size(100), height(1000);
static double f(int i, int j);

scene::scene() : running(true), ground("../data/ground.png"),
                 runway("../data/runway.png"), list(glGenLists(2)) {
    const double limit(1E4);

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

    glEndList();

    glNewList(list + 1, GL_COMPILE);
    glColor3d(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, runway);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex3d(-12.5, 0, -500);
    glTexCoord2d(1, 0);
    glVertex3d( 12.5, 0, -500);
    glTexCoord2d(0, 1);
    glVertex3d(-12.5, 0,  500);
    glTexCoord2d(1, 1);
    glVertex3d( 12.5, 0,  500);
    glEnd();
    glEndList();
}

bool scene::loop() const {
    return running;
}

void scene::stop() {
    running = false;
}

void scene::render() const {
    camera view;
    physics_get_location(&view.x.z, &view.x.y);
    physics_get_direction(&view.y.z, &view.y.y);
    view.z.y = -view.y.z;
    view.z.z = view.y.y;
    view.position();

    glPushMatrix();
    glTranslated(view.x.x, 0, view.x.z);
    glCallList(list);
    glPopMatrix();

    glCallList(list + 1);

    SDL_GL_SwapBuffers();
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

#include "mesh.hh"
#include "vector.hh"

#include <fstream>

mesh::mesh(const char *file) {
    std::ifstream input(file);
    vector p[4], n;

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);

    while (input.good()) {
        input >> p[0].x >> p[0].y >> p[0].z;
        input >> p[1].x >> p[1].y >> p[1].z;
        input >> p[2].x >> p[2].y >> p[2].z;
        input >> p[3].x >> p[3].y >> p[3].z;

        if (!input.good()) break;
        n = (p[1] - p[0]).cross(p[2] - p[0]);

        glNormal3d(n.x, n.y, n.z);
        glVertex3d(p[0].x, p[0].y, p[0].z);
        glVertex3d(p[1].x, p[1].y, p[1].z);
        glVertex3d(p[2].x, p[2].y, p[2].z);
        glVertex3d(p[3].x, p[3].y, p[3].z);
    }

    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEndList();
}

void mesh::render() const {
    glCallList(list);
}

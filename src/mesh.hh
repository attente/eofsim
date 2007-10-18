#ifndef MESH_HH
#define MESH_HH

#include "sdl.hh"

class mesh {
public:
    explicit mesh(const char *file);

    void render() const;

    GLuint list;
};

#endif

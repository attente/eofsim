#ifndef SCENE_HH
#define SCENE_HH

#include "sdl.hh"
#include "mesh.hh"
#include "texture.hh"

class scene {
public:
    scene();
    ~scene();

    void stop();
    bool loop() const;
    void render(int mode = 0) const;

private:
    bool running;

    texture ground;
    texture runway;
    texture shadow;
    texture stills;
    GLuint list;
    mesh tower;
    mesh obj;

    mutable int walkx, walky;
};

#endif

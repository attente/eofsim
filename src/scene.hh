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
    void render() const;

private:
    bool running;

    texture ground;
    texture runway;
    GLuint list;
    mesh obj;
};

#endif

#ifndef SCENE_HH
#define SCENE_HH

#include "sdl.hh"
#include "timer.hh"
#include "texture.hh"

class scene {
public:
    scene();

    bool loop() const;
    void start();
    void stop();

    void render() const;

    timer clock;

private:
    bool running;

    texture ground;
    texture runway;
    GLuint list;
};

#endif

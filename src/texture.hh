#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "sdl.hh"

class texture {
public:
    explicit texture(const char *file);

    operator GLuint() const;

    ~texture();

private:
    GLuint id;
};

#endif

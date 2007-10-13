#include "graphics.hh"
#include "physics.h"
#include "sdl.hh"

int main(int argc, char **argv) {
    int error(graphics_initialise());
    if (error) return error;
    const int delay(40);

    while (graphics_loop()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    graphics_stop();
                    break;
            }
        }

        int wait(static_cast< int >(graphics_delta()));
        if (wait < delay) SDL_Delay(delay - wait);

        graphics_render();
    }

    graphics_destroy();
}

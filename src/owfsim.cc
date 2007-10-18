#include "graphics.h"
#include "physics.h"
#include "timer.hh"
#include "sdl.hh"

int main(int argc, char **argv) {
    int error(graphics_initialise());
    if (error) return error;
    const int delay(40);

    physics_initialise (10000, 1000, -238, 0);
    physics_set_thrust(0);
    physics_set_flaps(0);

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
                        SDL_DEFAULT_REPEAT_INTERVAL);

    for (timer clock; graphics_loop(); clock.update()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            physics_set_thrust(physics_get_thrust() + 1);
                            break;
                        case SDL_BUTTON_RIGHT:
                            physics_set_thrust(physics_get_thrust() - 1);
                            break;
                    }

                    break;
                case SDL_MOUSEMOTION:
                    physics_set_flaps(event.motion.y * 17 / 600 - 8);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            graphics_stop();
                            break;
                        default:
                            break;
                    }

                    break;
                case SDL_QUIT:
                    graphics_stop();
                    break;
            }
        }

        int wait(static_cast< int >(clock.delta()));
        if (wait < delay) SDL_Delay(delay - wait);

        physics_update();
        graphics_render();
    }

    graphics_destroy();
}

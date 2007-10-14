#include "graphics.hh"
#include "physics.hh"
#include "timer.hh"
#include "sdl.hh"

int main(int argc, char **argv) {
    int error(graphics_initialise());
    if (error) return error;
    const int delay(40);

    physics_initialise (1000, 100, -200, 0);
    physics_set_thrust(8);
    physics_set_flaps(0);

    for (timer clock; graphics_loop(); clock.update()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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

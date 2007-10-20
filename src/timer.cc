/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "timer.hh"

timer::timer() : speed(1), tm(0), dt(0) {
    SDL_Init(SDL_INIT_TIMER);
    ms = SDL_GetTicks();
}

void timer::update() {
    Uint32 now(SDL_GetTicks());
    dt = speed * (now - ms);
    tm += dt;
    ms = now;
}

double timer::time() const {
    return tm;
}

double timer::delta() const {
    return dt;
}

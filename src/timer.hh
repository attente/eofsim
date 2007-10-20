/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef TIMER_HH
#define TIMER_HH

#include "sdl.hh"

class timer {
public:
    timer();

    void update();

    double time() const;
    double delta() const;

    double speed;

private:
    double tm, dt;
    Uint32 ms;
};

#endif

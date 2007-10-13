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

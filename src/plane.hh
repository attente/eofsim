#ifndef PLANE_HH
#define PLANE_HH

#include "timer.hh"
#include "vector.hh"

class plane {
public:
    plane(double dst, double alt, double dx, double dy);

    const vector &position() const;
    const vector &velocity() const;
    vector direction() const;

    int engine() const;
    void engine(int power);

    int wings() const;
    void wings(int angle);

    void start();
    void update();

    timer clock;

private:
    vector pos, vel;
    double impact;
    int thrust;
    int flaps;
};

#endif

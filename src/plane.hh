#ifndef PLANE_HH
#define PLANE_HH

#include "timer.hh"
#include "vector.hh"

class plane {
public:
    plane(double dst, double alt, double dx, double dy, double acc);

    const vector &position() const;
    const vector &velocity() const;
    const vector &direction() const;

    void engine(int power);
    void wings(int angle);

    void start();
    void update();

    timer clock;

private:
    int thrust;
    int flaps;

    vector x, y, z;
    double impact;
};

#endif

#include "plane.hh"

#include <cmath>

const double friction(0.90);
const double airbrake(0.20);
const double gravity(-9.8);
const double height(2.00);
const double match(0.15);
const double tilt(25);

const int limit(8);

plane::plane(double dst, double alt, double dx, double dy, double acc) :
x(0, alt, dst), y(0, dy, dx), z(y * acc / y.length()), thrust(0), flaps(0) {
}

const vector &plane::position() const {
    return x;
}

const vector &plane::velocity() const {
    return y;
}

const vector &plane::direction() const {
    return z;
}

void plane::engine(int power) {
    thrust = power;
    if (thrust > limit)
        thrust = limit;
    else if (thrust < -limit)
        thrust = -limit;
}

void plane::wings(int angle) {
    flaps = angle;
    if (flaps > limit)
        flaps = limit;
    else if (flaps < -limit)
        flaps = -limit;
}

void plane::start() {
    impact = 2;

    clock.update();
}

void plane::update() {
    double time(clock.delta() / 1000);

    x += y * time;
    y.y += gravity * time;
    if (thrust > 0) y += z * (thrust * time / limit);
    z = vector(1, 0, 0).rotate(z, flaps * tilt * time / limit);

    vector a(y * (1 / y.length())), b(z * (1 / z.length()));
    vector c(a * match), d(b * match);
    a += d; b += c;

    y = a * (y.length() / a.length());
    z = b * (z.length() / b.length());

    if (thrust >= 0) y *= std::pow(friction, time);
    else y *= std::pow(friction + airbrake * thrust / limit, time);

    if (x.y < height) {
        if (impact > 1)
            impact = y.y;

        x.y = height;
        y.y = 0;
    }

    clock.update();
}

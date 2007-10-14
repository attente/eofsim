#include "plane.hh"

#include <cmath>

const double drag(0.90);
const double brake(0.15);
const double height(2.00);
const double gravity(-9.81);

const double epsilon(1E-6);
const double acceleration(25);

const double bias(0);
const double tilt(1);

plane::plane(double dst, double alt, double dx, double dy) :
pos(0, alt, dst), vel(0, dy, dx), impact(2), thrust(0), flaps(0) {
}

const vector &plane::position() const {
    return pos;
}

const vector &plane::velocity() const {
    return vel;
}

vector plane::direction() const {
    return vel ? vel : vector(0, 0, -1);
}

int plane::engine() const {
    return thrust;
}

void plane::engine(int power) {
    thrust = power;
    if (thrust > 8)
        thrust = 8;
    else if (thrust < -8)
        thrust = -8;
}

int plane::wings() const {
    return flaps;
}

void plane::wings(int angle) {
    flaps = angle;
    if (flaps > 8)
        flaps = 8;
    else if (flaps < -8)
        flaps = -8;
}

void plane::start() {
    clock.update();
}

void plane::update() {
    double time(clock.delta() / 1000);

    vel.y += gravity * time;
    if (thrust >= 0) vel *= std::pow(drag, time);
    else vel *= std::pow(drag + brake * thrust / 8, time);

    if (thrust > 0) {
        double a(acceleration * thrust / 8);
        if (vel.length() < epsilon) vel.z -= a * time;
        else vel += vel * (a * time / vel.length());
    }

    double a((tilt * flaps / 8 + bias) * time);
    vel = vector(1, 0, 0).rotate(vel, a * vel.length());

    pos += vel * time;
    clock.update();

    if (pos.y < height) {
        if (impact > 1) impact = vel.y;

        pos.y = height;
        vel.y = 0;
    }
}

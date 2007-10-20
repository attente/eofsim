/*
 * Copyright © 2007 Ryan Lortie, William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

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
    double get_score (void);

    int engine() const;
    void engine(int power);

    int wings() const;
    void wings(int angle);
    void set_message (const char *msg, int prio);

    void landing_gear(void);
    void start();
    bool update();
    bool is_shaking (void);

    const char *message;
    timer clock;

private:
    bool gear_down;
    double score;
    double message_expiry;
    int message_prio;
    vector pos, vel;
    double impact;
    int thrust;
    int flaps;
    double start_time;
};

#endif

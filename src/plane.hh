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
    void set_message (const char *msg);

    void start();
    void update();

    const char *message;
    timer clock;

private:
    double score;
    double message_expiry;
    vector pos, vel;
    double impact;
    int thrust;
    int flaps;
};

#endif

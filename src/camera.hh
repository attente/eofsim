#ifndef CAMERA_HH
#define CAMERA_HH

#include "vector.hh"

class camera {
public:
    camera();

    void rotate(double rx, double ry);
    void move(const vector &d);
    void position() const;

    vector x, y, z;
};

#endif

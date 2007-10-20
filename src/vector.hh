/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef VECTOR_HH
#define VECTOR_HH

class vector {
public:
    explicit vector(double u = 0, double v = 0, double w = 0);

    vector transform(double a, double b, double c,
                     double d, double e, double f,
                     double g, double h, double i) const;
    vector rotate(const vector &v, double r) const;
    vector project(const vector &v) const;
    vector cross(const vector &v) const;
    double dot(const vector &v) const;
    double lengthsq() const;
    double length() const;

    operator bool() const;
    bool finite() const;
    bool null() const;

    const vector &operator+() const;
    vector &operator+();
    vector operator-() const;
    vector operator+(const vector &v) const;
    vector operator-(const vector &v) const;
    vector operator*(double s) const;
    vector &operator+=(const vector &v);
    vector &operator-=(const vector &v);
    vector &operator*=(double s);

    double x, y, z;
};

vector operator*(double s, const vector &v);

#endif

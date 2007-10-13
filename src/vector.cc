#include "vector.hh"

#include <cmath>

static bool zero(double x);

vector::vector(double u, double v, double w)
: x(u), y(v), z(w) {
}

vector vector::transform(double a, double b, double c,
                         double d, double e, double f,
                         double g, double h, double i) const {
    return vector(a * x + b * y + c * z,
                  d * x + e * y + f * z,
                  g * x + h * y + i * z);
}

vector vector::rotate(const vector &v, double r) const {
    double cosx(z / std::sqrt(y * y + z * z)),
           sinx(y / std::sqrt(y * y + z * z)),
           cosy(std::sqrt((y * y + z * z) / (x * x + y * y + z * z))),
           siny(-x / std::sqrt(x * x + y * y + z * z)),
           cosz(std::cos(r)),
           sinz(std::sin(r));

    if (!std::isfinite(cosx) || !std::isfinite(sinx)) {
        cosx = 1;
        sinx = 0;
    }

    if (!std::isfinite(cosy) || !std::isfinite(siny)) {
        cosy = 1;
        siny = 0;
    }

    return v.transform(    1,     0,     0,
                           0,  cosx, -sinx,
                           0,  sinx,  cosx)
            .transform( cosy,     0,  siny,
                           0,     1,     0,
                       -siny,     0,  cosy)
            .transform( cosz, -sinz,     0,
                        sinz,  cosz,     0,
                           0,     0,     1)
            .transform( cosy,     0, -siny,
                           0,     1,     0,
                        siny,     0,  cosy)
            .transform(    1,     0,     0,
                           0,  cosx,  sinx,
                           0, -sinx,  cosx);
}

vector vector::project(const vector &v) const {
    double s((v.x * x + v.y * y + v.z * z)
           / (  x * x +   y * y +   z * z));
    return vector(s * x, s * y, s * z);
}

vector vector::cross(const vector &v) const {
    return vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double vector::dot(const vector &v) const {
    return x * v.x + y * v.y + z * v.z;
}

double vector::lengthsq() const {
    return x * x + y * y + z * z;
}

double vector::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

vector::operator bool() const {
    return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) &&
           (!zero(x) || !zero(y) || !zero(z));
}

bool vector::finite() const {
    return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

bool vector::null() const {
    return zero(x) && zero(y) && zero(z);
}

const vector &vector::operator+() const {
    return *this;
}

vector &vector::operator+() {
    return *this;
}

vector vector::operator-() const {
    return vector(-x, -y, -z);
}

vector vector::operator+(const vector &v) const {
    return vector(x + v.x, y + v.y, z + v.z);
}

vector vector::operator-(const vector &v) const {
    return vector(x - v.x, y - v.y, z - v.z);
}

vector vector::operator*(double s) const {
    return vector(s * x, s * y, s * z);
}

vector &vector::operator+=(const vector &v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

vector &vector::operator-=(const vector &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

vector &vector::operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

vector operator*(double s, const vector &v) {
    return vector(s * v.x, s * v.y, s * v.z);
}

static bool zero(double x) {
    const double eps(1E-6);
    return x > -eps && x < eps;
}

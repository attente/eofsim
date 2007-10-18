#include "plane.hh"

#include <cmath>

const double drag(0.90);
const double brake(0.15);
const double gravity(-9.81);

const double epsilon(1E-6);
const double acceleration(30);

const double bias(0);
const double tilt(4E-3);

plane::plane(double dst, double alt, double dx, double dy) :
message (NULL), score (0.), message_expiry(0), pos(0, alt, dst), vel(0, dy, dx), impact(2), thrust(0), flaps(0) {
  score = dst * log (dst) + 0.001;
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
    start_time = clock.time();
    message = NULL;
    message_expiry = 0;
    gear_down = false;
}

bool plane::update() {
    double time(clock.delta() / 1000);
    bool was_grounded;

    was_grounded = pos.y <= 0;

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
    if (clock.time() > message_expiry)
    {
      message_prio = 0;
      message = NULL;
    }

    bool grounded;

    grounded = pos.y <= 0;

    if (grounded)
    {
      if (!was_grounded)
      {
        score += vel.y * 1000;

        if (gear_down)
        {
          set_message ("LANDED", 10);
          score += 100000;
        }
        else
          set_message ("NO LANDING GEAR", 10);
      }

      if (pos.z <= -282 || pos.z >= 1000)
      {
        set_message ("GRASS DAMAGE", 5);
        score += vel.z * time * 40;
      }

      if (vel.z >= -1)
      {
        set_message ("STOPPED", 100);
        return true;
      }

      pos.y = 0;
      vel.y = 0;
    }
    else
    {
      if (was_grounded)
      {
        set_message ("LIFTED OFF", 10);
        if (gear_down)
          score -= 100000;
      }
    }

    if (pos.z >= 5000)
      score -= fabs (pos.y - 1000) * 0.1;

    return false;
}

double
plane::get_score (void)
{
  return score - 0.1*(clock.time() - start_time) - fabs(pos.z)*log(fabs(pos.z));
}

void
plane::set_message (const char *msg, int prio)
{
  if (message_prio > prio)
    return;

  message = msg;
  message_expiry = clock.time() + 5000;
  message_prio = prio;
}

void
plane::landing_gear (void)
{
  static char lgmsg[50];

  if (gear_down)
    return;

  sprintf (lgmsg, "LANDING GEAR AT %.1fm\n", pos.y);
  score -= fabs (200 - pos.y) * 10;
  set_message (lgmsg, 5);
  gear_down = true;
}

bool
plane::is_shaking (void)
{
  return (pos.z <= -282 || pos.z >= 1000) && (pos.y == 0);
}

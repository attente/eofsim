/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef TRACKER_HH
#define TRACKER_HH

class tracker
{
  public:

    double x, y;
    double v, a;

    tracker (double z = 0);

    void update (double dt);

    operator double () const;

    tracker &operator= (double z);
    tracker &operator= (const tracker &t);
};

#endif

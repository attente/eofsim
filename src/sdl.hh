/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef SDL_HH
#define SDL_HH

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

void glPointParameterf  (GLenum         pname,
                         GLfloat        param);

void glPointParameterfv (GLenum         pname,
                         const GLfloat *params);

#ifdef __cplusplus
}
#endif

#endif

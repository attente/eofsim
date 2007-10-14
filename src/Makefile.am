bin_PROGRAMS = eofsim owfsim

physics = plane.cc physics.cc timer.cc vector.cc
graphics = camera.cc graphics.cc plane.cc physics.cc scene.cc texture.cc timer.cc vector.cc

AM_CFLAGS = -Wall -Wwrite-strings -Wmissing-prototypes
AM_CXXFLAGS = $(CFLAGS) $(sdl_CFLAGS)
AM_LDFLAGS = -lm $(sdl_LIBS) -lGL -lGLU -lSDL_image

eofsim_SOURCES = serial.c main.c serial.h $(graphics)
owfsim_SOURCES = owfsim.cc $(graphics)

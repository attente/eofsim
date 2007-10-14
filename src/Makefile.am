bin_PROGRAMS = eofsim owfsim

physics = plane.cc physics.cc timer.cc vector.cc
graphics = camera.cc graphics.cc scene.cc texture.cc

AM_CFLAGS = -Wall -Wwrite-strings -Wmissing-prototypes $(sdl_CFLAGS)
AM_CXXFLAGS = $(CFLAGS)
AM_LDFLAGS = -lm $(sdl_LIBS) -lGL -lGLU -lSDL_image

eofsim_SOURCES = serial.c main.c serial.h $(graphics) $(physics)
owfsim_SOURCES = owfsim.cc $(graphics) $(physics)

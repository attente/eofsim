bin_PROGRAMS = eofsim owfsim

graphics = camera.cc graphics.cc physics.c scene.cc texture.cc timer.cc vector.cc

AM_CFLAGS = -Wall -Wwrite-strings -Wmissing-prototypes
AM_CXXFLAGS = $(CFLAGS) $(sdl_CFLAGS)
AM_LDFLAGS = -lm $(sdl_LIBS) -lGL -lGLU -lSDL_image

eofsim_SOURCES = serial.c main.c serial.h physics.c
owfsim_SOURCES = owfsim.cc $(graphics)

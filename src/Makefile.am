bin_PROGRAMS = eofsim owfsim

graphics = camera.cc graphics.cc physics.c scene.cc texture.cc timer.cc vector.cc

CFLAGS = -Wall -Wwrite-strings -Wmissing-prototypes
CXXFLAGS = $(CFLAGS) $(sdl_CFLAGS)
LDFLAGS = -lm $(sdl_LIBS) -lGL -lGLU -lSDL_image

eofsim_SOURCES = serial.c main.c serial.h physics.c
owfsim_SOURCES = owfsim.cc $(graphics)

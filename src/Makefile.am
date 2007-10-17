bin_PROGRAMS = eofsim owfsim netwatch
noinst_PROGRAMS = mkconv
GENERATED = conversion.c

core = vector.cc
physics = plane.cc physics.cc timer.cc
graphics = camera.cc graphics.cc scene.cc texture.cc

AM_CFLAGS = -Wall -Wwrite-strings -Wmissing-prototypes $(sdl_CFLAGS)
AM_CXXFLAGS = -Wall -Wwrite-strings $(sdl_CFLAGS)
AM_LDFLAGS = -lm $(sdl_LIBS) -lGL -lGLU -lSDL_image

eofsim_SOURCES = serial.c main.c serial.h $(graphics) $(physics) $(core) netsend.c net.c conversion.c
owfsim_SOURCES = owfsim.cc $(graphics) $(physics) $(core)
netwatch_SOURCES = $(graphics) netphysics.c netmain.c $(core) net.c

conversion.c: mkconv
	./mkconv > conversion.c

mkconv_SOURCES = mkconv.c

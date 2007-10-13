#ifndef EOFSIM_HH
#define EOFSIM_HH

int graphics_initialise();
void graphics_destroy();
void graphics_render();

void graphics_stop();
bool graphics_loop();
double graphics_delta();

#endif

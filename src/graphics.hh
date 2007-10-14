#ifndef EOFSIM_HH
#define EOFSIM_HH

int graphics_initialise(void);
void graphics_destroy(void);
void graphics_render(void);

void graphics_stop(void);
bool graphics_loop(void);
double graphics_delta(void);

#endif

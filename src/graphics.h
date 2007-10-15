#ifndef _graphics_h_
#define _graphics_h_

#ifdef __cplusplus
extern "C" {
#endif

int graphics_initialise(void);
void graphics_destroy(void);
void graphics_render(void);

void graphics_stop(void);
bool graphics_loop(void);
double graphics_delta(void);

void graphics_print(const char *s, double x, double y);

#ifdef __cplusplus
}
#endif

#endif /* _graphics_h_ */

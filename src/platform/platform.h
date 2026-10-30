#ifndef RACER_PLATFORM_MINIFB_H
#define RACER_PLATFORM_MINIFB_H
#include <stdbool.h>
#include <stdint.h>

typedef struct Platform Platform;

typedef enum { KEY_ESCAPE, KEY_UP, KEY_DOWN } Key;

Platform *platform_open(const char *title, int width, int height);
bool platform_present(Platform *p, const uint32_t *pixels);
bool platform_key_down(const Platform *p, Key key);
double platform_time(const Platform *p);
void platform_close(Platform *p);

#endif // RACER_PLATFORM_MINIFB_H

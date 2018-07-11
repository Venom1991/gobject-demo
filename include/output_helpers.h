#ifndef GOBJECT_DEMO_HELPERS_H
#define GOBJECT_DEMO_HELPERS_H

#include <glib.h>

#ifdef G_OS_UNIX

#define COLOR_RESET_CODE   "\x1b[0m"
#define COLOR_RED_CODE     "\x1b[31m"
#define COLOR_GREEN_CODE   "\x1b[32m"
#define COLOR_YELLOW_CODE  "\x1b[33m"
#define COLOR_BLUE_CODE    "\x1b[34m"
#define COLOR_MAGENTA_CODE "\x1b[35m"
#define COLOR_CYAN_CODE    "\x1b[36m"

#endif

#ifdef G_OS_WIN32

#define COLOR_RESET_CODE   G_STRINGIFY (666) /* not used, left for consistency's sake */
#define COLOR_RED_CODE     G_STRINGIFY (4)
#define COLOR_GREEN_CODE   G_STRINGIFY (2)
#define COLOR_YELLOW_CODE  G_STRINGIFY (14)
#define COLOR_BLUE_CODE    G_STRINGIFY (1)
#define COLOR_MAGENTA_CODE G_STRINGIFY (5)
#define COLOR_CYAN_CODE    G_STRINGIFY (3)

#endif

const gchar *get_reset_color_code (void);

void         print_colored_output (const gchar *output,
                                   const gchar *color_code);

void         reset_color          (const gchar *reset_color_code);

#endif //GOBJECT_DEMO_HELPERS_H

#ifndef GOBJECT_DEMO_RENDERABLE_H
#define GOBJECT_DEMO_RENDERABLE_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum
{
    COLOR_UNDEFINED,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN
} Color;

#define SHAPES_TYPE_RENDERABLE (renderable_get_type ())

G_DECLARE_INTERFACE (Renderable, renderable, SHAPES, RENDERABLE, GObject)

struct _RenderableInterface
{
    GTypeInterface parent_iface;

    void (*paint) (Renderable  *self,
                   Color        color,
                   GError     **error);
    void (*draw)  (Renderable  *self);
};

void renderable_paint (Renderable  *self,
                       Color        color,
                       GError     **error);

void renderable_draw  (Renderable  *self);

#define PROP_RENDERABLE_COLOR                  "color"
#define PROP_RENDERABLE_COLOR_ANSI_ESCAPE_CODE "color-ansi-escape-code"

G_END_DECLS

#endif /* GOBJECT_DEMO_RENDERABLE_H */

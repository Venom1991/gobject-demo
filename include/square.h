#ifndef GOBJECT_DEMO_SQUARE_H
#define GOBJECT_DEMO_SQUARE_H

#include "shape.h"

#include <glib-object.h>

G_BEGIN_DECLS

#define SHAPES_TYPE_SQUARE (square_get_type ())
#define square_new(...) (g_object_new (SHAPES_TYPE_SQUARE, ##__VA_ARGS__, NULL))

G_DECLARE_FINAL_TYPE (Square, square, SHAPES, SQUARE, Shape)

#define PROP_SQUARE_SIDE "side"

G_END_DECLS

#endif /* GOBJECT_DEMO_SQUARE_H */

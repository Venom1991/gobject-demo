#ifndef GOBJECT_DEMO_CIRCLE_H
#define GOBJECT_DEMO_CIRCLE_H

#include "shape.h"

#include <glib-object.h>

G_BEGIN_DECLS

#define SHAPES_TYPE_CIRCLE (circle_get_type ())
#define circle_new(...) (g_object_new (SHAPES_TYPE_CIRCLE, ##__VA_ARGS__, NULL))

G_DECLARE_FINAL_TYPE (Circle, circle, SHAPES, CIRCLE, Shape)

#define PROP_CIRCLE_RADIUS   "radius"
#define PROP_CIRCLE_DIAMETER "diameter"

G_END_DECLS

#endif /* GOBJECT_DEMO_CIRCLE_H */

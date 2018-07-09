#ifndef GOBJECT_DEMO_MOVABLE_POINT_H
#define GOBJECT_DEMO_MOVABLE_POINT_H

#include <glib-object.h>

#include "point.h"

G_BEGIN_DECLS

#define SHAPES_TYPE_MOVABLE_POINT (movable_point_get_type ())
#define movable_point_new(...) (g_object_new (SHAPES_TYPE_MOVABLE_POINT, ##__VA_ARGS__, NULL))

G_DECLARE_FINAL_TYPE (MovablePoint, movable_point, SHAPES, MOVABLE_POINT, Point)

G_END_DECLS

#endif /* GOBJECT_DEMO_MOVABLE_POINT_H */

#ifndef GOBJECT_DEMO_POINT_H
#define GOBJECT_DEMO_POINT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SHAPES_TYPE_POINT (point_get_type ())
#define point_new(...) (g_object_new (SHAPES_TYPE_POINT, ##__VA_ARGS__, NULL))

G_DECLARE_DERIVABLE_TYPE (Point, point, SHAPES, POINT, GObject)

struct _PointClass
{
    GObjectClass parent_class;
};

#define PROP_POINT_X_COORDINATE "x-coordinate"
#define PROP_POINT_Y_COORDINATE "y-coordinate"

G_END_DECLS

#endif /* GOBJECT_DEMO_POINT_H */

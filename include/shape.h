#ifndef GOBJECT_DEMO_SHAPE_H
#define GOBJECT_DEMO_SHAPE_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SHAPES_TYPE_SHAPE (shape_get_type ())

G_DECLARE_DERIVABLE_TYPE (Shape, shape, SHAPES, SHAPE, GObject)

struct _ShapeClass
{
  GObjectClass parent_class;

  gdouble (*compute_area)      (Shape *self);
  gdouble (*compute_perimeter) (Shape *self);

  gpointer     padding[8];
};

gdouble shape_compute_area      (Shape *self);
gdouble shape_compute_perimeter (Shape *self);

#define PROP_SHAPE_CAPTION "caption"

G_END_DECLS

#endif /* GOBJECT_DEMO_SHAPE_H */

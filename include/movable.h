#ifndef GOBJECT_DEMO_MOVABLE_H
#define GOBJECT_DEMO_MOVABLE_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum
{
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT,
} Direction;

#define SHAPES_TYPE_MOVABLE (movable_get_type ())

G_DECLARE_INTERFACE (Movable, movable, SHAPES, MOVABLE, GObject)

struct _MovableInterface
{
  GTypeInterface parent_iface;

  void (*move) (Movable    *self,
                Direction   direction,
                GError    **error);
};

void movable_move (Movable    *self,
                   Direction   direction,
                   GError    **error);

G_END_DECLS

#endif /* GOBJECT_DEMO_MOVABLE_H */

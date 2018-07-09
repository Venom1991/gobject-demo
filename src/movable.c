#include "movable.h"

G_DEFINE_INTERFACE (Movable, movable, G_TYPE_OBJECT)

static void
movable_default_init (MovableInterface *iface)
{
  /* NOP */
}

void
movable_move (Movable    *self,
              Direction   direction,
              GError    **error)
{
  MovableInterface *iface;

  g_return_if_fail (SHAPES_IS_MOVABLE (self));

  iface = SHAPES_MOVABLE_GET_IFACE (self);

  g_return_if_fail (iface->move != NULL);

  iface->move (self,
               direction,
               error);
}

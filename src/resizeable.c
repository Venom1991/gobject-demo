#include "resizeable.h"
#include "renderable.h"

G_DEFINE_INTERFACE (Resizeable, resizeable, SHAPES_TYPE_RENDERABLE)

static void
resizeable_default_init (ResizeableInterface *iface)
{
  /* NOP */
}

void
resizeable_resize (Resizeable *self, gint percent)
{
  ResizeableInterface *iface;

  g_return_if_fail (SHAPES_IS_RESIZEABLE (self));

  iface = SHAPES_RESIZEABLE_GET_IFACE (self);

  g_return_if_fail (iface->resize != NULL);

  iface->resize (self, percent);
}

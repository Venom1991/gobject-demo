#include "renderable.h"

G_DEFINE_INTERFACE (Renderable, renderable, G_TYPE_OBJECT)

static void
renderable_default_init (RenderableInterface *iface)
{
  g_object_interface_install_property (iface,
                                       g_param_spec_uint (PROP_RENDERABLE_COLOR,
                                                          "Color",
                                                          "A renderable object's current color.",
                                                          COLOR_UNDEFINED,
                                                          COLOR_CYAN,
                                                          COLOR_UNDEFINED,
                                                          G_PARAM_READABLE));

  g_object_interface_install_property (iface,
                                       g_param_spec_string (PROP_RENDERABLE_COLOR_ANSI_ESCAPE_CODE,
                                                            "Color ANSI escape code",
                                                            "A renderable object's current color as an ANSI escape code.",
                                                            NULL,
                                                            G_PARAM_READABLE));
}

void
renderable_paint (Renderable  *self,
                  Color        color,
                  GError     **error)
{
  RenderableInterface *iface;

  g_return_if_fail (SHAPES_IS_RENDERABLE (self));

  iface = SHAPES_RENDERABLE_GET_IFACE (self);

  g_return_if_fail (iface->paint != NULL);

  iface->paint (self,
                color,
                error);
}

void
renderable_draw (Renderable *self)
{
  RenderableInterface *iface;

  g_return_if_fail (SHAPES_IS_RENDERABLE (self));

  iface = SHAPES_RENDERABLE_GET_IFACE (self);

  g_return_if_fail (iface->draw != NULL);

  iface->draw (self);
}

#ifndef GOBJECT_DEMO_RESIZEABLE_H
#define GOBJECT_DEMO_RESIZEABLE_H

#include <glib-object.h>

G_BEGIN_DECLS

#define SHAPES_TYPE_RESIZEABLE (resizeable_get_type ())

G_DECLARE_INTERFACE (Resizeable, resizeable, SHAPES, RESIZEABLE, GObject)

struct _ResizeableInterface
{
    GTypeInterface parent_iface;

    void (*resize) (Resizeable *self,
                    gint        percent);
};

void resizeable_resize (Resizeable *self,
                        gint        percent);

G_END_DECLS

#endif /* GOBJECT_DEMO_RESIZEABLE_H */

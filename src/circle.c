#include "circle.h"
#include "point.h"
#include "renderable.h"
#include "resizeable.h"

#include <math.h>

#include <glib/gprintf.h>

struct _Circle
{
  Shape parent_instance;
};

typedef struct
{
  gdouble  radius;
  gdouble  diameter;
  Point   *center;
} CirclePrivate;

enum
{
  PROP_RADIUS = 1,
  PROP_DIAMETER,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

static void    circle_renderable_interface_init (RenderableInterface *iface);

static void    circle_resizeable_interface_init (ResizeableInterface *iface);

static void    circle_draw                      (Renderable          *self);

static void    circle_resize                    (Resizeable          *self,
                                                 gint                 percent);

static gdouble circle_compute_area              (Shape               *self);

static gdouble circle_compute_perimeter         (Shape               *self);

static void    circle_constructed               (GObject             *object);

static void    circle_get_property              (GObject             *object,
                                                 guint                property_id,
                                                 GValue              *value,
                                                 GParamSpec          *pspec);

static void    circle_set_property              (GObject             *object,
                                                 guint                property_id,
                                                 const GValue        *value,
                                                 GParamSpec          *pspec);

static void    circle_dispose                   (GObject             *object);

G_DEFINE_TYPE_WITH_CODE (Circle, circle, SHAPES_TYPE_SHAPE,
                         G_ADD_PRIVATE (Circle)
                         G_IMPLEMENT_INTERFACE (SHAPES_TYPE_RENDERABLE,
                                                circle_renderable_interface_init)
                         G_IMPLEMENT_INTERFACE (SHAPES_TYPE_RESIZEABLE,
                                                circle_resizeable_interface_init))

static void
circle_class_init (CircleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  ShapeClass *shape_class = SHAPES_SHAPE_CLASS (klass);

  shape_class->compute_area = circle_compute_area;
  shape_class->compute_perimeter = circle_compute_perimeter;

  object_class->constructed = circle_constructed;
  object_class->get_property = circle_get_property;
  object_class->set_property = circle_set_property;
  object_class->dispose = circle_dispose;

  obj_properties[PROP_RADIUS] =
    g_param_spec_double (PROP_CIRCLE_RADIUS,
                         "Radius",
                         "Length of the circle's radius.",
                         0.0,
                         G_MAXDOUBLE,
                         0.0,
                         G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  obj_properties[PROP_DIAMETER] =
    g_param_spec_double (PROP_CIRCLE_DIAMETER,
                         "Diameter",
                         "Length of the circle's diameter.",
                         0.0,
                         G_MAXDOUBLE,
                         0.0,
                         G_PARAM_READABLE);

  g_object_class_install_properties (object_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
circle_init (Circle *self)
{
  /* NOP */
}

static void
circle_renderable_interface_init (RenderableInterface *iface)
{
  iface->draw = circle_draw;
}

static void circle_resizeable_interface_init (ResizeableInterface *iface)
{
  iface->resize = circle_resize;
}

static void
circle_draw (Renderable *self)
{
  g_return_if_fail (SHAPES_IS_CIRCLE (self));

  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (self));
  gdouble radius = priv->radius;
  gdouble diameter = priv->diameter;
  gint diameter_as_gint = (gint) ceil (diameter);
  g_autofree const gchar *ansi_escape_code = NULL;

  g_object_get (self,
                PROP_RENDERABLE_COLOR_ANSI_ESCAPE_CODE, &ansi_escape_code,
                NULL);

  g_assert (ansi_escape_code != NULL);

  for (gint i = 0; i <= diameter_as_gint; ++i)
    {
      for (gint j = 0; j <= diameter_as_gint; ++j)
        {
          gdouble distance = sqrt (pow (i - radius, 2) + pow (j - radius, 2));

          if (distance > (radius - 0.5) && distance < (radius + 0.5))
            {
              g_autofree gchar *output = g_strdup_printf ("%s\t*", ansi_escape_code);

              g_printf (output);
            }
          else
            {
              g_printf ("\t");
            }
        }

      g_printf ("\n");
    }

  g_printf (ANSI_COLOR_RESET "\n");
}

static void
circle_resize (Resizeable *self,
               gint        percent)
{
  g_return_if_fail (SHAPES_IS_CIRCLE (self));
  g_return_if_fail (percent != 0);

  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (self));
  gdouble radius = priv->radius;
  gdouble size_difference = ((gdouble) abs (percent) / 100) * radius;

  if (percent > 0)
    radius += size_difference;
  else
    radius -= size_difference;

  priv->radius = radius;
  priv->diameter = radius * 2;
}

static gdouble
circle_compute_area (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_CIRCLE (self), 0.0);

  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (self));
  gdouble radius = priv->radius;

  return pow (radius, 2) * G_PI;
}

static gdouble
circle_compute_perimeter (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_CIRCLE (self), 0.0);

  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (self));
  gdouble diameter = priv->diameter;

  return diameter * G_PI;
}

static void
circle_constructed (GObject *object)
{
  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (object));

  gdouble radius = priv->radius;
  guint radius_as_guint = (guint) ceil (radius);
  Point *center = point_new (PROP_POINT_X_COORDINATE, radius_as_guint,
                             PROP_POINT_Y_COORDINATE, radius_as_guint);

  priv->diameter = radius * 2;
  priv->center = center;

  G_OBJECT_CLASS (circle_parent_class)->constructed (object);
}

static void
circle_get_property (GObject    *object,
                     guint       property_id,
                     GValue     *value,
                     GParamSpec *pspec)
{
  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (object));

  switch (property_id)
    {
    case PROP_RADIUS:
      g_value_set_double (value, priv->radius);
      break;

    case PROP_DIAMETER:
      g_value_set_double (value, priv->diameter);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
circle_set_property (GObject      *object,
                     guint         property_id,
                     const GValue *value,
                     GParamSpec   *pspec)
{
  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (object));

  switch (property_id)
    {
    case PROP_RADIUS:
      priv->radius = g_value_get_double (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
circle_dispose (GObject *object)
{
  CirclePrivate *priv = circle_get_instance_private (SHAPES_CIRCLE (object));

  if (priv->center != NULL)
    g_clear_object (&priv->center);

  G_OBJECT_CLASS (circle_parent_class)->dispose (object);
}

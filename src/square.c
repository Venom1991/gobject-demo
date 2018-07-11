#include "square.h"
#include "movable_point.h"
#include "renderable.h"
#include "movable.h"
#include "output_helpers.h"

#include <math.h>

#include <glib/gprintf.h>

struct _Square
{
  Shape parent_instance;
};

typedef struct
{
  gdouble       side;
  MovablePoint *top_left;
  MovablePoint *bottom_right;
} SquarePrivate;

enum
{
  PROP_SIDE = 1,
  N_PROPERTIES
};

#define SIDES_COUNT 4

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

static void    square_renderable_interface_init (RenderableInterface  *iface);

static void    square_movable_interface_init    (MovableInterface     *iface);

static void    square_draw                      (Renderable           *self);

static void    square_move                      (Movable              *self,
                                                 Direction             direction,
                                                 GError              **error);

static gdouble square_compute_area              (Shape                *self);

static gdouble square_compute_perimeter         (Shape                *self);

static void    square_constructed               (GObject              *object);

static void    square_get_property              (GObject              *object,
                                                 guint                 property_id,
                                                 GValue               *value,
                                                 GParamSpec           *pspec);

static void    square_set_property              (GObject              *object,
                                                 guint                 property_id,
                                                 const GValue         *value,
                                                 GParamSpec           *pspec);

static void    square_dispose                   (GObject              *object);

G_DEFINE_TYPE_WITH_CODE (Square, square, SHAPES_TYPE_SHAPE,
                         G_ADD_PRIVATE (Square)
                         G_IMPLEMENT_INTERFACE (SHAPES_TYPE_RENDERABLE,
                                                square_renderable_interface_init)
                         G_IMPLEMENT_INTERFACE (SHAPES_TYPE_MOVABLE,
                                                square_movable_interface_init))

static void
square_class_init (SquareClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  ShapeClass *shape_class = SHAPES_SHAPE_CLASS (klass);

  shape_class->compute_area = square_compute_area;
  shape_class->compute_perimeter = square_compute_perimeter;

  object_class->constructed = square_constructed;
  object_class->get_property = square_get_property;
  object_class->set_property = square_set_property;
  object_class->dispose = square_dispose;

  obj_properties[PROP_SIDE] =
    g_param_spec_double (PROP_SQUARE_SIDE,
                         "Side",
                         "Length of the square's side.",
                         0.0,
                         G_MAXDOUBLE,
                         0.0,
                         G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  g_object_class_install_properties (object_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
square_init (Square *self)
{
  /* NOP */
}

static void
square_renderable_interface_init (RenderableInterface *iface)
{
  iface->draw = square_draw;
}

static void
square_movable_interface_init (MovableInterface *iface)
{
  iface->move = square_move;
}

static void
square_draw (Renderable *self)
{
  g_return_if_fail (SHAPES_IS_SQUARE (self));

  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (self));
  const gchar *reset_color_code = get_reset_color_code ();
  g_autofree const gchar *color_escape_code = NULL;

  g_object_get (self,
                PROP_RENDERABLE_COLOR_OUTPUT_CODE, &color_escape_code,
                NULL);

  g_assert (color_escape_code != NULL);

  Point *top_left = SHAPES_POINT (priv->top_left);
  guint top_left_x = 0;
  guint top_left_y = 0;
  Point *bottom_right = SHAPES_POINT (priv->bottom_right);
  guint bottom_right_x = 0;
  guint bottom_right_y = 0;

  g_object_get (top_left,
                PROP_POINT_X_COORDINATE, &top_left_x,
                PROP_POINT_Y_COORDINATE, &top_left_y,
                NULL);
  g_object_get (bottom_right,
                PROP_POINT_X_COORDINATE, &bottom_right_x,
                PROP_POINT_Y_COORDINATE, &bottom_right_y,
                NULL);

  guint x_difference = bottom_right_x - top_left_x;
  guint y_difference = bottom_right_y - top_left_y;

  for (gint i = 0; i < bottom_right_y - y_difference; ++i)
    g_printf ("\n");

  for (gint i = top_left_x; i < bottom_right_x; ++i)
    {
      for (gint j = 0; j < bottom_right_x - x_difference; ++j)
        g_printf (" ");

      for (gint j = top_left_y; j < bottom_right_y; ++j)
        {
          if ((i == top_left_x || i == bottom_right_x - 1) ||
              (j == top_left_y || j == bottom_right_y - 1))
            print_colored_output (" *", color_escape_code);
          else
            g_printf ("  ");
        }

      g_printf ("\n");
    }

  g_printf ("\n");
  reset_color (reset_color_code);
}

static void
square_move (Movable    *self,
             Direction   direction,
             GError    **error)
{
  g_return_if_fail (SHAPES_IS_SQUARE (self));
  g_return_if_fail (error == NULL || *error == NULL);

  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (self));

  Movable *top_left = SHAPES_MOVABLE (priv->top_left);
  Movable *bottom_right = SHAPES_MOVABLE (priv->bottom_right);
  GError *temporary_error = NULL;

  movable_move (top_left,
                direction,
                &temporary_error);

  if (temporary_error != NULL)
    {
      g_propagate_error (error, temporary_error);

      return;
    }

  movable_move (bottom_right,
                direction,
                &temporary_error);

  if (temporary_error != NULL)
    {
      g_propagate_error (error, temporary_error);

      return;
    }
}

static gdouble
square_compute_area (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_SQUARE (self), 0.0);

  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (self));
  gdouble side = priv->side;

  return pow (side, 2);
}

static gdouble
square_compute_perimeter (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_SQUARE (self), 0.0);

  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (self));
  gdouble side = priv->side;

  return side * SIDES_COUNT;
}

static void
square_constructed (GObject *object)
{
  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (object));

  gdouble side = priv->side;
  gint side_as_gint = (gint) ceil (side);
  MovablePoint *top_left = movable_point_new (PROP_POINT_X_COORDINATE, 0,
                                              PROP_POINT_Y_COORDINATE, 0);
  MovablePoint *bottom_right = movable_point_new (PROP_POINT_X_COORDINATE, side_as_gint,
                                                  PROP_POINT_Y_COORDINATE, side_as_gint);

  priv->top_left = top_left;
  priv->bottom_right = bottom_right;

  G_OBJECT_CLASS (square_parent_class)->constructed (object);
}

static void
square_get_property (GObject    *object,
                     guint       property_id,
                     GValue     *value,
                     GParamSpec *pspec)
{
  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (object));

  switch (property_id)
    {
    case PROP_SIDE:
      g_value_set_double (value, priv->side);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
square_set_property (GObject      *object,
                     guint         property_id,
                     const GValue *value,
                     GParamSpec   *pspec)
{
  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (object));

  switch (property_id)
    {
    case PROP_SIDE:
      priv->side = g_value_get_double (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
square_dispose (GObject *object)
{
  SquarePrivate *priv = square_get_instance_private (SHAPES_SQUARE (object));

  if (priv->top_left != NULL)
    g_clear_object (&priv->top_left);

  if (priv->bottom_right != NULL)
    g_clear_object (&priv->bottom_right);

  G_OBJECT_CLASS (square_parent_class)->dispose (object);
}

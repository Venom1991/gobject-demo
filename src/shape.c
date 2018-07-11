#include "shape.h"
#include "renderable.h"
#include "errors.h"
#include "output_helpers.h"

typedef struct
{
  Color  color;
  gchar *caption;
} ShapePrivate;

enum
{
  PROP_CAPTION = 1,
  PROP_COLOR,
  PROP_COLOR_OUTPUT_CODE,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

G_DEFINE_QUARK (shapes-shape-error-quark, shapes_shape_error)
#define SHAPES_SHAPE_ERROR (shapes_shape_error_quark ())

static void         shape_renderable_interface_init (RenderableInterface  *iface);

static void         shape_paint                     (Renderable           *self,
                                                     Color                 color,
                                                     GError              **error);

static const gchar *shape_color_to_output_code (Color color);

static void         shape_get_property              (GObject              *object,
                                                     guint                 property_id,
                                                     GValue               *value,
                                                     GParamSpec           *pspec);

static void         shape_set_property              (GObject              *object,
                                                     guint                 property_id,
                                                     const GValue         *value,
                                                     GParamSpec           *pspec);

static void         shape_finalize                  (GObject              *object);

G_DEFINE_ABSTRACT_TYPE_WITH_CODE (Shape, shape, G_TYPE_OBJECT,
                                  G_ADD_PRIVATE (Shape)
                                  G_IMPLEMENT_INTERFACE (SHAPES_TYPE_RENDERABLE,
                                                         shape_renderable_interface_init))

static void
shape_class_init (ShapeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = shape_get_property;
  object_class->set_property = shape_set_property;
  object_class->finalize = shape_finalize;

  klass->compute_area = NULL;
  klass->compute_perimeter = NULL;

  GParamSpec *caption_pspec = g_param_spec_string (PROP_SHAPE_CAPTION,
                                                   "Caption",
                                                   "Shape's caption.",
                                                   NULL,
                                                   G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  g_object_class_install_property (object_class,
                                   PROP_CAPTION,
                                   caption_pspec);
  g_object_class_override_property (object_class,
                                    PROP_COLOR,
                                    PROP_RENDERABLE_COLOR);
  g_object_class_override_property (object_class,
                                    PROP_COLOR_OUTPUT_CODE,
                                    PROP_RENDERABLE_COLOR_OUTPUT_CODE);
}

static void
shape_init (Shape *self)
{
  /* NOP */
}

static void
shape_renderable_interface_init (RenderableInterface *iface)
{
  iface->paint = shape_paint;
  iface->draw = NULL; // needs to be implemented in derived classes
}

gdouble
shape_compute_area (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_SHAPE (self), 0.0);

  ShapeClass *klass = SHAPES_SHAPE_GET_CLASS (self);

  g_return_val_if_fail (klass->compute_area != NULL, 0.0);

  return klass->compute_area (self);
}

gdouble
shape_compute_perimeter (Shape *self)
{
  g_return_val_if_fail (SHAPES_IS_SHAPE (self), 0.0);

  ShapeClass *klass = SHAPES_SHAPE_GET_CLASS (self);

  g_return_val_if_fail (klass->compute_perimeter != NULL, 0.0);

  return klass->compute_perimeter (self);
}

static void
shape_paint (Renderable  *self,
             Color        color,
             GError     **error)
{
  g_return_if_fail (SHAPES_IS_SHAPE (self));
  g_return_if_fail (error == NULL || *error == NULL);

  ShapeError error_code = SHAPES_SHAPE_ERROR_UNDEFINED;
  const gchar *error_message = NULL;

  if (color == COLOR_UNDEFINED)
    {
      error_code = SHAPES_SHAPE_PAINT_ERROR_COLOR_UNDEFINED;
      error_message = "Parameter \"color\" must be defined.";

      g_set_error (error,
                   SHAPES_SHAPE_ERROR,
                   error_code,
                   error_message);
    }

  ShapePrivate *priv = shape_get_instance_private (SHAPES_SHAPE (self));

  priv->color = color;
}

static const gchar *
shape_color_to_output_code (Color color)
{
  gchar *output_code = NULL;

  switch (color)
    {
    case COLOR_UNDEFINED:
      g_return_val_if_reached (NULL);
    case COLOR_RED:
      output_code = COLOR_RED_CODE;
      break;
    case COLOR_GREEN:
      output_code = COLOR_GREEN_CODE;
      break;
    case COLOR_YELLOW:
      output_code = COLOR_YELLOW_CODE;
      break;
    case COLOR_BLUE:
      output_code = COLOR_BLUE_CODE;
      break;
    case COLOR_MAGENTA:
      output_code = COLOR_MAGENTA_CODE;
      break;
    case COLOR_CYAN:
      output_code = COLOR_CYAN_CODE;
      break;
    }

  return output_code;
}

static void
shape_get_property (GObject    *object,
                    guint       property_id,
                    GValue     *value,
                    GParamSpec *pspec)
{
  ShapePrivate *priv = shape_get_instance_private (SHAPES_SHAPE (object));

  switch (property_id)
    {
    case PROP_CAPTION:
      g_value_set_string (value, priv->caption);
      break;

    case PROP_COLOR:
      g_value_set_uint (value, priv->color);
      break;

    case PROP_COLOR_OUTPUT_CODE:
      {
        const gchar *color_output_code = shape_color_to_output_code (priv->color);

        g_value_set_string (value, color_output_code);
      }
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
shape_set_property (GObject      *object,
                    guint         property_id,
                    const GValue *value,
                    GParamSpec   *pspec)
{
  ShapePrivate *priv = shape_get_instance_private (SHAPES_SHAPE (object));

  switch (property_id)
    {
    case PROP_CAPTION:
      priv->caption = g_value_dup_string (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
shape_finalize (GObject *object)
{
  ShapePrivate *priv = shape_get_instance_private (SHAPES_SHAPE (object));

  if (priv->caption != NULL)
    g_free (priv->caption);

  G_OBJECT_CLASS (shape_parent_class)->finalize (object);
}

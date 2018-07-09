#include "point.h"

typedef struct
{
  guint x_coordinate;
  guint y_coordinate;
} PointPrivate;

enum
{
  PROP_X_COORDINATE = 1,
  PROP_Y_COORDINATE,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL };

static void point_get_property (GObject      *object,
                                guint         property_id,
                                GValue       *value,
                                GParamSpec   *pspec);

static void point_set_property (GObject      *object,
                                guint         property_id,
                                const GValue *value,
                                GParamSpec   *pspec);

G_DEFINE_TYPE_WITH_PRIVATE (Point, point, G_TYPE_OBJECT)

static void
point_class_init (PointClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = point_get_property;
  object_class->set_property = point_set_property;

  obj_properties[PROP_X_COORDINATE] =
    g_param_spec_uint (PROP_POINT_X_COORDINATE,
                       "X coordinate",
                       "Point's X coordinate.",
                       0,
                       G_MAXUINT,
                       0,
                       G_PARAM_CONSTRUCT | G_PARAM_READWRITE);

  obj_properties[PROP_Y_COORDINATE] =
    g_param_spec_uint (PROP_POINT_Y_COORDINATE,
                       "Y coordinate",
                       "Point's Y coordinate.",
                       0,
                       G_MAXUINT,
                       0,
                       G_PARAM_CONSTRUCT | G_PARAM_READWRITE);

  g_object_class_install_properties (object_class,
                                     N_PROPERTIES,
                                     obj_properties);
}

static void
point_init (Point *self)
{
  /* NOP */
}

static void
point_get_property (GObject     *object,
                    guint        property_id,
                    GValue      *value,
                    GParamSpec  *pspec)
{
  PointPrivate *priv = point_get_instance_private (SHAPES_POINT (object));

  switch (property_id)
    {
      case PROP_X_COORDINATE:
        g_value_set_uint (value, priv->x_coordinate);
      break;

      case PROP_Y_COORDINATE:
        g_value_set_uint (value, priv->y_coordinate);
      break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
point_set_property (GObject      *object,
                    guint         property_id,
                    const GValue *value,
                    GParamSpec   *pspec)
{
  PointPrivate *priv = point_get_instance_private (SHAPES_POINT (object));

  switch (property_id)
    {
    case PROP_X_COORDINATE:
      priv->x_coordinate = g_value_get_uint (value);
      break;

    case PROP_Y_COORDINATE:
      priv->y_coordinate = g_value_get_uint (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

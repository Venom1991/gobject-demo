#include "movable_point.h"
#include "movable.h"
#include "errors.h"

struct _MovablePoint
{
  Point parent_instance;
};

G_DEFINE_QUARK (shapes-movable-point-error-quark, shapes_movable_point_error)
#define SHAPES_MOVABLE_POINT_ERROR (shapes_movable_point_error_quark ())

static void movable_point_movable_interface_init (MovableInterface  *iface);

static void movable_point_move                   (Movable           *self,
                                                  Direction          direction,
                                                  GError           **error);

G_DEFINE_TYPE_WITH_CODE (MovablePoint, movable_point, SHAPES_TYPE_POINT,
                         G_IMPLEMENT_INTERFACE (SHAPES_TYPE_MOVABLE,
                                                movable_point_movable_interface_init))

static void
movable_point_class_init (MovablePointClass *klass)
{
  /* NOP */
}

static void
movable_point_init (MovablePoint *self)
{
  /* NOP */
}

static void
movable_point_movable_interface_init (MovableInterface *iface)
{
  iface->move = movable_point_move;
}

static void
movable_point_move (Movable    *self,
                    Direction   direction,
                    GError    **error)
{
  g_return_if_fail (SHAPES_IS_MOVABLE_POINT (self));
  g_return_if_fail (error == NULL || *error == NULL);

  guint x_coordinate = 0;
  guint y_coordinate = 0;
  MovablePointError error_code = SHAPES_MOVABLE_POINT_ERROR_UNDEFINED;
  const gchar *error_message = NULL;

  g_object_get (self,
                PROP_POINT_X_COORDINATE, &x_coordinate,
                PROP_POINT_Y_COORDINATE, &y_coordinate,
                NULL);

  switch (direction)
    {
    case DIRECTION_UP:
      if (y_coordinate != 0)
        {
          y_coordinate -= 1;
        }
      else
        {
          error_code = SHAPES_MOVABLE_POINT_ERROR_Y_COORDINATE_ZERO;
          error_message = "Unable to move up, Y coordinate's value is zero.";
        }
      break;
    case DIRECTION_DOWN:
      if (y_coordinate != G_MAXUINT)
        {
          y_coordinate += 1;
        }
      else
        {
          error_code = SHAPES_MOVABLE_POINT_ERROR_Y_COORDINATE_MAXIMUM_VALUE;
          error_message = "Unable to move down, Y coordinate's value is already at its maximum.";
        }
      break;
    case DIRECTION_LEFT:
      if (x_coordinate != 0)
        {
          x_coordinate -= 1;
        }
      else
        {
          error_code = SHAPES_MOVABLE_POINT_ERROR_X_COORDINATE_ZERO;
          error_message = "Unable to move left, X coordinate's value is zero.";
        }
      break;
    case DIRECTION_RIGHT:
      if (x_coordinate != G_MAXUINT)
        {
          x_coordinate += 1;
        }
      else
        {
          error_code = SHAPES_MOVABLE_POINT_ERROR_X_COORDINATE_MAXIMUM_VALUE;
          error_message = "Unable to move right, X coordinate's value is already at its maximum.";
        }
      break;
    }

  if (error_code != SHAPES_MOVABLE_POINT_ERROR_UNDEFINED)
    {
      g_set_error (error,
                   SHAPES_MOVABLE_POINT_ERROR,
                   error_code,
                   error_message);

      return;
    }

  g_object_set (self,
                PROP_POINT_X_COORDINATE, x_coordinate,
                PROP_POINT_Y_COORDINATE, y_coordinate,
                NULL);
}

#include <stdio.h>
#include <stdlib.h>

#include <glib/gprintf.h>

#include "renderable.h"
#include "resizeable.h"
#include "movable.h"
#include "circle.h"
#include "square.h"

gint
main (void)
{
  g_autoptr (Shape) circle = circle_new (PROP_SHAPE_CAPTION, "Circle",
                                         PROP_CIRCLE_RADIUS, 8.0); /* upcasting Circle to Shape */
  g_autoptr (Shape) square = square_new (PROP_SHAPE_CAPTION, "Square",
                                         PROP_SQUARE_SIDE, 12.345); /* upcasting Square to Shape */

  gpointer shapes[] = { circle, square };
  Color colors[] = { COLOR_GREEN, COLOR_RED };

  for (gint i = 0; i < G_N_ELEMENTS (shapes); ++i)
    {
      Shape *shape = SHAPES_SHAPE (shapes[i]);
      g_autofree gchar *caption = NULL;
      gdouble area = shape_compute_area (shape);
      gdouble perimeter = shape_compute_perimeter (shape);
      g_autoptr (GError) error = NULL;

      g_object_get (shape,
                    PROP_SHAPE_CAPTION, &caption,
                    NULL);

      g_printf ("SHAPE: %s\n", caption);
      g_printf ("\t- AREA: %f\n", area);
      g_printf ("\t- PERIMETER: %f\n", perimeter);
      g_printf ("\n");

      // both Circle and Square implement Renderable
      Renderable *renderable = SHAPES_RENDERABLE (shape);

      g_printf ("Painting the shape...\n");

      renderable_paint (renderable,
                        colors[i],
                        &error);

      if (error != NULL)
        {
          g_fprintf (stderr, "Unable to paint the shape - reason: \"%s\"\n", error->message);

          return EXIT_FAILURE;
        }

      renderable_draw (renderable);

      // checking if object "shape" is of type Resizeable
      if (SHAPES_IS_RESIZEABLE (shape))
        {
          Resizeable *resizeable = SHAPES_RESIZEABLE (shape);

          g_printf ("Resizing the shape...\n");

          resizeable_resize (resizeable, -50);
          renderable_draw (renderable);
        }

      // same check as above, this time with another interface (Movable)
      if (SHAPES_IS_MOVABLE (shape))
        {
          Movable *movable = SHAPES_MOVABLE (shape);

          const guint down_direction_steps = 2;
          const guint right_direction_steps = 3;

          g_printf ("Moving the shape...\n");

          for (guint j = 0; j < down_direction_steps; ++j)
            {
              movable_move (movable,
                            DIRECTION_DOWN,
                            &error);

              if (error != NULL)
                {
                  g_fprintf (stderr, "Unable to move the shape down - reason: \"%s\"\n", error->message);

                  return EXIT_FAILURE;
                }
            }

          for (guint j = 0; j < right_direction_steps; ++j)
            {
              movable_move (movable,
                            DIRECTION_RIGHT,
                            &error);

              if (error != NULL)
                {
                  g_fprintf (stderr, "Unable to move the shape right - reason: \"%s\"\n", error->message);

                  return EXIT_FAILURE;
                }
            }

          renderable_draw (renderable);
        }
    }

  return EXIT_SUCCESS;
}

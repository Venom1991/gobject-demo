#ifndef GOBJECT_DEMO_ERRORS_H
#define GOBJECT_DEMO_ERRORS_H

typedef enum
{
    SHAPES_SHAPE_ERROR_UNDEFINED = 0,
    SHAPES_SHAPE_PAINT_ERROR_COLOR_UNDEFINED,
    SHAPES_SHAPE_N_ERRORS
} ShapeError;

typedef enum
{
    SHAPES_MOVABLE_POINT_ERROR_UNDEFINED = SHAPES_SHAPE_N_ERRORS,
    SHAPES_MOVABLE_POINT_ERROR_X_COORDINATE_ZERO,
    SHAPES_MOVABLE_POINT_ERROR_Y_COORDINATE_ZERO,
    SHAPES_MOVABLE_POINT_ERROR_X_COORDINATE_MAXIMUM_VALUE,
    SHAPES_MOVABLE_POINT_ERROR_Y_COORDINATE_MAXIMUM_VALUE,
    SHAPES_MOVABLE_POINT_N_ERRORS
} MovablePointError;

#endif /* GOBJECT_DEMO_ERRORS_H */

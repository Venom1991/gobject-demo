cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(gobject_demo VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_executable(gobject_demo
    include/circle.h
    include/errors.h
    include/movable.h
    include/movable_point.h
    include/output_helpers.h
    include/point.h
    include/renderable.h
    include/resizeable.h
    include/shape.h
    include/square.h
    main.c
    src/circle.c
    src/movable.c
    src/movable_point.c
    src/output_helpers.c
    src/point.c
    src/renderable.c
    src/resizeable.c
    src/shape.c
    src/square.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

# GLib & GObject
pkg_check_modules(GLIB_GOBJECT glib-2.0>=2.54 gobject-2.0>=2.54)

target_link_libraries(${PROJECT_NAME} -lm)

if(GLIB_GOBJECT_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_GOBJECT_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLIB_GOBJECT_LIBRARIES} ${GLIB_GOBJECT_LDFLAGS})

    add_definitions(${GLIB_GOBJECT_CFLAGS} ${GLIB_GOBJECT_CFLAGS_OTHER})

    message( STATUS "GLIB_GOBJECT_LIBRARIES: " ${GLIB_GOBJECT_LIBRARIES} )
    message( STATUS "GLIB_GOBJECT_LIBRARY_DIRS: " ${GLIB_GOBJECT_LIBRARY_DIRS} )
    message( STATUS "GLIB_GOBJECT_LDFLAGS: " ${GLIB_GOBJECT_LDFLAGS} )
    message( STATUS "GLIB_GOBJECT_LDFLAGS_OTHER: " ${GLIB_GOBJECT_LDFLAGS_OTHER} )
    message( STATUS "GLIB_GOBJECT_INCLUDE_DIRS: " ${GLIB_GOBJECT_INCLUDE_DIRS} )
    message( STATUS "GLIB_GOBJECT_CFLAGS: " ${GLIB_GOBJECT_CFLAGS} )
    message( STATUS "GLIB_GOBJECT_CFLAGS_OTHER: " ${GLIB_GOBJECT_CFLAGS_OTHER} )
else()
    message( FATAL_ERROR "GLib & GObject >= 2.54 are required, exiting." )
endif()

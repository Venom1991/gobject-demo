#include "output_helpers.h"

#include <glib/gprintf.h>

#ifdef G_OS_WIN32

#include <windows.h>

WORD
get_parsed_attributes (const gchar *color_code)
{
  guint64 parsed_code = 0;
  GError *error = NULL;

  if (!g_ascii_string_to_unsigned (color_code,
                                   10,
                                   0,
                                   G_MAXUINT16,
                                   &parsed_code,
                                   &error))
    {
      g_fprintf (stderr, "Unable to parse the color code - reason: \"%s\"\n", error->message);

      exit (EXIT_FAILURE);
    }

  return (WORD) parsed_code;
}

const gchar *
get_reset_color_code (void)
{
  HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
  WORD wOldColorAttributes;
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;

  if (!GetConsoleScreenBufferInfo (hConsole, &csbInfo))
  {
    g_fprintf (stderr, "GetConsoleScreenBufferInfo call failed!\n");

    exit (EXIT_FAILURE);
  }

  wOldColorAttributes = csbInfo.wAttributes;

  return g_strdup_printf ("%d", wOldColorAttributes);
}

void
print_colored_output (const gchar *text,
                      const gchar *color_code)
{
  HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
  WORD wAttributes = get_parsed_attributes (color_code);

  SetConsoleTextAttribute (hConsole, wAttributes);

  g_printf (text);
}

void
reset_color (const gchar *reset_color_code)
{
  HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
  WORD wAttributes = get_parsed_attributes (reset_color_code);

  SetConsoleTextAttribute (hConsole, wAttributes);

  g_printf ("\n");
  g_free ((gpointer) reset_color_code);
}

#endif

#ifdef G_OS_UNIX

const gchar *
get_reset_color_code (void)
{
  return COLOR_RESET_CODE;
}

void
print_colored_output (const gchar *text,
                      const gchar *color_code)
{
  g_autofree gchar *output = g_strconcat (color_code,
                                          text,
                                          NULL);

  g_printf (output);
}

void
reset_color (const gchar *reset_color_code)
{
  g_autofree gchar *output = g_strdup_printf ("%s\n", reset_color_code);

  g_printf (output);
}

#endif

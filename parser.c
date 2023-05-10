/* INCLUDES */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

/* DEFINES */
#define INC_LINES 1024
#define INC_CHARS 1024

/* DATA */
char **lines;
size_t tot_lines = 0;
size_t tot_chars = 0;
char c;

/* MAIN */
char **logparse (char *logf, size_t *f_length)
{
  struct gzFile_s *file = gzopen (logf, "r");

  if (file == NULL)
  {
      printf ("%s", logf);
      printf ("!!! Error\nUnable to open file.\n");
      return NULL;
  }

  lines = malloc (sizeof (char *) * INC_CHARS);

  do
  {
      c = gzgetc (file);

      if (gzeof (file))
	  {
	      if (tot_chars != 0)
	      {
	          lines[tot_lines] = realloc (lines[tot_lines], tot_chars + 1);
	          lines[tot_lines][tot_chars] = '\0';
	          tot_lines++;
	      }
	      break;
	  }
      if (tot_chars == 0)
	    lines[tot_lines] = malloc (INC_CHARS);

      lines[tot_lines][tot_chars] = c;
      tot_chars++;

      if (c == '\n')
	  {
		lines[tot_lines] = realloc (lines[tot_lines], tot_chars + 1);
	    lines[tot_lines][tot_chars] = '\0';

	    tot_lines++;
	    tot_chars = 0;

	    if (tot_lines % INC_LINES == 0)
	    {
		  size_t new_sz = tot_lines + INC_LINES;
	      lines = realloc (lines, sizeof (char *) * new_sz);
	    }
	  }
      else if (tot_chars % INC_CHARS == 0)
	  {
	    size_t new_sz = tot_chars + INC_CHARS;
	    lines[tot_lines] = realloc (lines[tot_lines], new_sz);
	  }
  } while (true);

  lines = realloc (lines, sizeof (char *) * tot_lines);
	*f_length = tot_lines;
  return lines;

	for (size_t i = 0; i < tot_lines; i++)
		free (lines[i]);
	free (lines);
	gzclose (file);
}

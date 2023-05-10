#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_EMERGE_LOG_DIR "/var/log/emerge.log"

int arg_val (int verbose_in, int *verbose, char *logfile, int limit_in, int *limit,
    int predict_in, int *predict, char *outfile, int merge_in, int *merge,
    int unmerge_in, int *unmerge)
{
  if ((merge_in == 1 || unmerge_in == 1 || predict_in == 1 ) && (verbose_in == 1))
  {
    printf ("omitting -v, [Return] to continue..\n");
    getchar ();
    *verbose = 0;
    return 0;
  }
  if ((unmerge_in == 1 || predict_in == 1) && (merge_in == 1))
  {
    printf ("omitting -m, [Return] to continue..\n");
    getchar ();
    *merge = 0;
    return 0;
  }
  if ((predict_in == 1 || merge_in == 1) && (unmerge_in == 1))
  {
    printf ("omitting -u, [Return] to continue..");
    getchar ();
    *unmerge = 0;
    return 0;
  }
  if ((merge_in == 1 || unmerge_in == 1) && (predict_in == 1))
  {
    printf ("omitting -p, [Return] to continue..");
    getchar ();
    *predict = 0;
    return 0;
  }
  return 0;
}

void portage_fetch_err (char *err) {
  printf ("%s", err);
  printf ("Using standard portage logfile (/var/log/emerge.log).\n");
}

char *p_env = "EMERGE_LOG_DIR";
char delim_eq[] = "=";
char delim_nl[] = "\n";
char delim_hash[] = "#";

char *portage_fetch (char *conf_arr[], size_t f_len)
{
  for (size_t i = 0; i < f_len; i++)
  {
    if (strstr (conf_arr[i], p_env) != NULL)
    {
      if (strstr (conf_arr[i], delim_hash) != NULL)
      {
        char *err = "!!! Warning: envvar \"EMERGE_LOG_DIR\" is commented out.\n";
        portage_fetch_err (err);
        
        char *logdir = STD_EMERGE_LOG_DIR;
        return logdir;
      }

      char *buf = strtok (conf_arr[i], delim_eq);
      buf[0] = '\0';
      char *logdir = strtok (NULL, delim_nl);

      char *filename = "/emerge.log";
      size_t l_len = strlen (filename);
      strncat (logdir, filename, l_len);
      return logdir;
    }
    if (i == f_len - 1 && strstr (conf_arr[i], p_env) == NULL)
    {
      char *err = "!!! Warning: envvar \"EMERGE_LOG_DIR\" has not been set.\n";
      portage_fetch_err (err);
      
      char *logdir = STD_EMERGE_LOG_DIR;
      return logdir;
    }
    else
    {
      continue;
    }
  }
  return NULL;
}



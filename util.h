#ifndef UTIL_H
#define UTIL_H


#include <stdlib.h>

int arg_val (int verbose_in, int *verbose, char *logfile, int limit_in, int *limit,
    int predict_in, int *predict, char *outfile, int merge_in, int *merge,
    int unmerge_in, int *unmerge);

void *portage_fetch_err (char *err);

char *portage_fetch (char *conf_arr[], size_t f_len);


#endif

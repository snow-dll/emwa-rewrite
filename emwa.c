/* INCLUDES */
#include "util.h"
#include "parser.h"
#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>

/* DEFINES */
#define USAGE 0x123
#define PORTAGE_CONF "/etc/portage/make.conf"
#define EMWA_DEFAULT_LOG_DIR "/var/log/emerge.log"
#define EMWA_DEFAULT_LIM 20

/* DATA */
const char *argp_program_version = "clop v0.1.0";
const char *argp_program_bug_address = "k3nny.wx@mailfence.com";

static char args_doc[] = "";
static char doc[] = "EMWA - Emerge Monitor written in C\nniggetr";

struct arguments
{
  int verbose;
  char *logfile;
  char *package;
  int limit;
  int predict;
  char *outfile;
  int merge;
  int unmerge;
};

static struct argp_option opts[] = {
  {"help",      'h',    0,          0,  "Show this message",          -1},
  {"version",   'V',    0,          0,  "Show version information",   0},
  {"usage",     USAGE,  0,          0,  "Show usage",                 0},
  {"verbose",   'v',    0,          0,  "Produce verbose output",     0},
  {"logfile",   'f',    "LOGFILE",  0,  "Read from LOGFILE",          0},
  {"package",   'p',    "PACKAGE",  0,  "Specify a package",          0},
  {"limit",     'l',    "LIM",      0,  "Set a limit for ETA avg",    0},
  {"predict",   'P',    "PACKAGE",  0,  "Predict build time",        0},
  {"outfile",   'o',    "FILE",     0,
    "Write to FILE instead of stdout",                                0},
  {"merge",     'm',    0,          0,  "Print merge history",        0},
  {"unmerge",   'u',    0,          0,  "Print unmerge history",      0},
  {0}
};

/* ARG PARSER */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
  {

    case 'h':
      argp_state_help (state, state->out_stream, ARGP_HELP_STD_HELP);
      break;
    case USAGE:
      argp_state_help (state, state->out_stream, ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
      break;

    case 'v':   arguments->verbose = 1;               break;
    case 'f':   arguments->logfile = arg;             break;
    case 'p':   arguments->package = arg;             break;
    case 'l':   arguments->limit = EMWA_DEFAULT_LIM;  break;
    case 'P':   arguments->predict = 1;               break;
    case 'o':   arguments->outfile = arg;             break;
    case 'm':   arguments->merge = 1;                 break;
    case 'u':   arguments->unmerge = 1;               break;

    default:    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { opts, parse_opt, args_doc, doc, 0, 0, 0 };

/* MAIN */
int main (int argc, char **argv)
{
  struct arguments arguments;

  arguments.verbose = 0;
  arguments.logfile = "";
  arguments.limit = 0;
  arguments.predict = 0;
  arguments.outfile = "";
  arguments.merge = 0;
  arguments.unmerge = 0;

  int verbose = arguments.verbose;
  int limit = arguments.limit;
  int predict = arguments.predict;
  int merge = arguments.merge;
  int unmerge = arguments.unmerge;

  argp_parse (&argp, argc, argv, ARGP_NO_HELP, 0, &arguments);

  arg_val (arguments.verbose, &verbose, arguments.logfile, arguments.limit, &limit,
      arguments.predict, &predict, arguments.outfile, arguments.merge, &merge,
      arguments.unmerge, &unmerge);

  size_t f_len;
  char **portage_conf_file = logparse (PORTAGE_CONF, &f_len);
  char *portage_log_dir = portage_fetch (portage_conf_file, f_len);

  char **parsed_logfile = logparse (portage_log_dir, &f_len);
  
  return 0;
}

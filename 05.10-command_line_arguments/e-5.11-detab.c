/* Modify the programs entab and detab (written as exercises in Chapter 1) to accept
   a list of tab stops as arguments. Use the default tab settings if there are no
   arguments. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* macros */
#define NO_ARG          0
#define REQUIRED_ARG    1
#define OPTIONAL_ARG    2

/* types */

/* GETOPT_LONG_OPTION_T: The type of long option */
typedef struct GETOPT_LONG_OPTION_T {
  char *name;         /* the name of the long option */
  int has_arg;        /* one of the above macros */
  int *flag;          /* determines if getopt_long() returns a
		       * value for a long option; if it is
		       * non-NULL, 0 is returned as a function
		       * value and the value of val is stored in
		       * the area pointed to by flag.  Otherwise,
		       * val is returned. */
  int val;            /* determines the value to return if flag is
		       * NULL. */
} GETOPT_LONG_OPTION_T;

typedef enum GETOPT_ORDERING_T {
  PERMUTE,
  RETURN_IN_ORDER,
  REQUIRE_ORDER
} GETOPT_ORDERING_T;

/* globally-defined variables */
char *optarg = NULL;
int optind = 0;
int opterr = 1;
int optopt = '?';

/* statically-defined variables */

static char *program_name;
/* if nonzero, it means tab every x characters */
static unsigned long tab_every = 8;
/* -i: only handle initial tabs/spaces */
static int flag_initial = 0;
/* expand tabs into spaces */
static int flag_expand = 1;
static unsigned long *tab_stop_list = NULL;
static size_t num_tab_stops = 0;
static size_t num_tab_stops_allocked = 0;
static int show_help = 0;
static int show_version = 0;
static char *shortopts = "it:";
static GETOPT_LONG_OPTION_T longopts[] =
  {
    {"initial", NO_ARG, NULL, 'i'},
    {"tabs", REQUIRED_ARG, NULL, 't'},

    {"help", NO_ARG, &show_help, 1},
    {"version", NO_ARG, &show_version, 1},
    {NULL, 0, 0, 0}
  };

/* functions */

/* reverse_argv_elements:  reverses num elements starting at argv */
static void reverse_argv_elements(char **argv, int num)
{
  int i;
  char *tmp;

  for (i = 0; i < (num >> 1); i++) {
    tmp = argv[i];
    argv[i] = argv[num - i - 1];
    argv[num - i - 1] = tmp;
  }
}

/* permute: swap two blocks of argv-elements given their lengths */
static void permute(char **argv, int len1, int len2)
{
  reverse_argv_elements(argv, len1);
  reverse_argv_elements(argv, len1 + len2);
  reverse_argv_elements(argv, len2);
}

/* is_option: is this argv-element an option or the end of the option
   list? */
static int is_option(char *argv_element, int only)
{
  return ((argv_element == NULL)
	  || (argv_element[0] == '-')
	  || (only && argv_element[0] == '+'));
}

/* getopt_internal:  the function that does all the dirty work */
static int getopt_internal(int argc, char **argv, char *shortopts,
			   GETOPT_LONG_OPTION_T * longopts, int *longind, int only)
{
  GETOPT_ORDERING_T ordering = PERMUTE;
  static size_t optwhere = 0;
  size_t permute_from = 0;
  int num_nonopts = 0;
  int optindex = 0;
  size_t match_chars = 0;
  char *possible_arg = NULL;
  int longopt_match = -1;
  int has_arg = -1;
  char *cp;
  int arg_next = 0;

  /* first, deal with silly parameters and easy stuff */
  if (argc == 0 || argv == NULL || (shortopts == NULL && longopts == NULL))
    return (optopt = '?');
  if (optind >= argc || argv[optind] == NULL)
    return EOF;
  if (strcmp(argv[optind], "--") == 0) {
    optind++;
    return EOF;
  }
  /* if this is our first time through */
  if (optind == 0)
    optind = optwhere = 1;

  /* define ordering */
  if (shortopts != NULL && (*shortopts == '-' || *shortopts == '+')) {
    ordering = (*shortopts == '-') ? RETURN_IN_ORDER : REQUIRE_ORDER;
    shortopts++;
  }
  else
    ordering = (getenv("POSIXLY_CORRECT") != NULL) ? REQUIRE_ORDER :
      PERMUTE;

  /* based on ordering, find our next option, if we're at the beginning of
   * one
   */
  if (optwhere == 1) {
    switch (ordering) {
    case PERMUTE:
      permute_from = optind;
      num_nonopts = 0;
      while (!is_option(argv[optind], only)) {
	optind++;
	num_nonopts++;
      }
      if (argv[optind] == NULL) {
	/* no more options */
	optind = permute_from;
	return EOF;
      } else if (strcmp(argv[optind], "--") == 0) {
	/* no more options, but have to get `--' out of the way */
	permute(argv + permute_from, num_nonopts, 1);
	optind = permute_from + 1;
	return EOF;
      }
      break;
    case RETURN_IN_ORDER:
      if (!is_option(argv[optind], only)) {
	optarg = argv[optind++];
	return (optopt = 1);
      }
      break;
    case REQUIRE_ORDER:
      if (!is_option(argv[optind], only))
	return EOF;
      break;
    }
  }
  /* we've got an option, so parse it */

  /* first, is it a long option? */
  if (longopts != NULL
      && (memcmp(argv[optind], "--", 2) == 0
	  || (only && argv[optind][0] == '+'))
      && optwhere == 1) {
    /* handle long options */
    if (memcmp(argv[optind], "--", 2) == 0)
      optwhere = 2;
    longopt_match = -1;
    possible_arg = strchr(argv[optind] + optwhere, '=');
    if (possible_arg == NULL) {
      /* no =, so next argv might be arg */
      match_chars = strlen(argv[optind]);
      possible_arg = argv[optind] + match_chars;
      match_chars = match_chars - optwhere;
    }
    else
      match_chars = (possible_arg - argv[optind]) - optwhere;
    for (optindex = 0; longopts[optindex].name != NULL; optindex++) {
      if (memcmp(argv[optind] + optwhere,
		 longopts[optindex].name,
		 match_chars) == 0) {
	/* do we have an exact match? */
	if (match_chars == (int) (strlen(longopts[optindex].name))) {
	  longopt_match = optindex;
	  break;
	}
	/* do any characters match? */
	else {
	  if (longopt_match < 0)
	    longopt_match = optindex;
	  else {
	    /* we have ambiguous options */
	    if (opterr)
	      fprintf(stderr, "%s: option `%s' is ambiguous "
		      "(could be `--%s' or `--%s')\n",
		      argv[0],
		      argv[optind],
		      longopts[longopt_match].name,
		      longopts[optindex].name);
	    return (optopt = '?');
	  }
	}
      }
    }
    if (longopt_match >= 0)
      has_arg = longopts[longopt_match].has_arg;
  }
  /* if we didn't find a long option, is it a short option? */
  if (longopt_match < 0 && shortopts != NULL) {
    cp = strchr(shortopts, argv[optind][optwhere]);
    if (cp == NULL) {
      /* couldn't find option in shortopts */
      if (opterr)
	fprintf(stderr,
		"%s: invalid option -- `-%c'\n",
		argv[0],
		argv[optind][optwhere]);
      optwhere++;
      if (argv[optind][optwhere] == '\0') {
	optind++;
	optwhere = 1;
      }
      return (optopt = '?');
    }
    has_arg = ((cp[1] == ':')
	       ? ((cp[2] == ':') ? OPTIONAL_ARG : REQUIRED_ARG)
	       : NO_ARG);
    possible_arg = argv[optind] + optwhere + 1;
    optopt = *cp;
  }
  /* get argument and reset optwhere */
  arg_next = 0;
  switch (has_arg) {
  case OPTIONAL_ARG:
    if (*possible_arg == '=')
      possible_arg++;
    if (*possible_arg != '\0') {
      optarg = possible_arg;
      optwhere = 1;
    }
    else
      optarg = NULL;
    break;
  case REQUIRED_ARG:
    if (*possible_arg == '=')
      possible_arg++;
    if (*possible_arg != '\0') {
      optarg = possible_arg;
      optwhere = 1;
    }
    else if (optind + 1 >= argc) {
      if (opterr) {
	fprintf(stderr, "%s: argument required for option `",
		argv[0]);
	if (longopt_match >= 0)
	  fprintf(stderr, "--%s'\n", longopts[longopt_match].name);
	else
	  fprintf(stderr, "-%c'\n", *cp);
      }
      optind++;
      return (optopt = ':');
    }
    else {
      optarg = argv[optind + 1];
      arg_next = 1;
      optwhere = 1;
    }
    break;
  case NO_ARG:
    if (longopt_match < 0) {
      optwhere++;
      if (argv[optind][optwhere] == '\0')
	optwhere = 1;
    }
    else
      optwhere = 1;
    optarg = NULL;
    break;
  }

  /* do we have to permute or otherwise modify optind? */
  if (ordering == PERMUTE && optwhere == 1 && num_nonopts != 0) {
    permute(argv + permute_from, num_nonopts, 1 + arg_next);
    optind = permute_from + 1 + arg_next;
  }
  else if (optwhere == 1)
    optind = optind + 1 + arg_next;

  /* finally return */
  if (longopt_match >= 0) {
    if (longind != NULL)
      *longind = longopt_match;
    if (longopts[longopt_match].flag != NULL) {
      *(longopts[longopt_match].flag) = longopts[longopt_match].val;
      return 0;
    }
    else
      return longopts[longopt_match].val;
  }
  else
    return optopt;
}

int getopt_long(int argc, char **argv, char *shortopts,
		GETOPT_LONG_OPTION_T * longopts, int *longind)
{
  return getopt_internal(argc, argv, shortopts, longopts, longind, 0);
}

void help(void)
{
  puts( "OPTIONS" );
  puts( "" );
  puts( "-i, --initial   When shrinking, make initial spaces/tabs on a line tabs" );
  puts( "                and expand every other tab on the line into spaces." );
  puts( "-t=tablist,     Specify list of tab stops.  Default is every 8 characters." );
  puts( "--tabs=tablist, The parameter tablist is a list of tab stops separated by" );
  puts( "-tablist        commas; if no commas are present, the program will put a" );
  puts( "                tab stop every x places, with x being the number in the" );
  puts( "                parameter." );
  puts( "" );
  puts( "--help          Print usage message and exit successfully." );
  puts( "" );
  puts( "--version       Print version information and exit successfully." );
}

void version(void)
{
  puts( "detab - expand tabs into spaces" );
  puts( "Version 1.0" );
  puts( "Written by Gregory Pietsch" );
}

/* allocate memory, die on error */
void *xmalloc(size_t n)
{
  void *p = malloc(n);

  if (p == NULL) {
    fprintf(stderr, "%s: out of memory\n", program_name);
    exit(EXIT_FAILURE);
  }
  return p;
}

/* reallocate memory, die on error */
void *xrealloc(void *p, size_t n)
{
  void *s;

  if (n == 0) {
    if (p != NULL)
      free(p);
    return NULL;
  }
  if (p == NULL)
    return xmalloc(n);
  s = realloc(p, n);
  if (s == NULL) {
    fprintf(stderr, "%s: out of memory\n", program_name);
    exit(EXIT_FAILURE);
  }
  return s;
}

/* Determine the location of the first character in the string s1
 * that is not a character in s2.  The terminating null is not
 * considered part of the string.
 */
char *xstrcpbrk(char *s1, char *s2)
{
  char *sc1;
  char *sc2;

  for (sc1 = s1; *sc1 != '\0'; sc1++)
    for (sc2 = s2;; sc2++)
      if (*sc2 == '\0')
	return sc1;
      else if (*sc1 == *sc2)
	break;
  return NULL;                /* terminating nulls match */
}

/* compare function for qsort() */
int ul_cmp(const void *a, const void *b)
{
  unsigned long *ula = (unsigned long *) a;
  unsigned long *ulb = (unsigned long *) b;

  return (*ula < *ulb) ? -1 : (*ula > *ulb);
}

/* handle a tab stop list -- assumes param isn't NULL */
void handle_tab_stops(char *s)
{
  char *p;
  unsigned long ul;
  size_t len = strlen(s);

  if (xstrcpbrk(s, "0123456789,") != NULL) {
    /* funny param */
    fprintf(stderr, "%s: invalid parameter\n", program_name);
    exit(EXIT_FAILURE);
  }
  if (strchr(s, ',') == NULL) {
    tab_every = strtoul(s, NULL, 10);
    if (tab_every == 0)
      tab_every = 8;
  }
  else {
    tab_stop_list = xrealloc(tab_stop_list,
			     (num_tab_stops_allocked += len) * (sizeof(unsigned long)));
    for (p = s; (p = strtok(p, ",")) != NULL; p = NULL) {
      ul = strtoul(p, NULL, 10);
      tab_stop_list[num_tab_stops++] = ul;
    }
    qsort(tab_stop_list, num_tab_stops, sizeof(unsigned long),
	  ul_cmp);
  }
}

void parse_args(int argc, char **argv)
{
  int opt;

  do {
    switch ((opt = getopt_long(argc, argv, shortopts, longopts, NULL))) {
    case 'i':               /* initial */
      flag_initial = 1;
      break;
    case 't':               /* tab stops */
      handle_tab_stops(optarg);
      break;
    case '?':               /* invalid option */
      fprintf(stderr, "For help, type:\n\t%s --help\n", program_name);
      exit(EXIT_FAILURE);
    case 1:
    case 0:
      if (show_help || show_version) {
	if (show_help)
	  help();
	if (show_version)
	  version();
	exit(EXIT_SUCCESS);
      }
      break;
    default:
      break;
    }
  } while (opt != EOF);
}

/* output exactly n spaces */
void output_spaces(size_t n)
{
  int x = n;                  /* assume n is small */

  printf("%*s", x, "");
}

/* get next highest tab stop */
unsigned long get_next_tab(unsigned long x)
{
  size_t i;

  if (tab_stop_list == NULL) {
    /* use tab_every */
    x += (tab_every - (x % tab_every));
    return x;
  }
  else {
    for (i = 0; i < num_tab_stops && tab_stop_list[i] <= x; i++);
    return (i >= num_tab_stops) ? 0 : tab_stop_list[i];
  }
}

/* the function that does the dirty work */
void tab(FILE * f)
{
  unsigned long linelength = 0;
  int c;
  int in_initials = 1;
  size_t num_spaces = 0;
  unsigned long next_tab;

  while ((c = getc(f)) != EOF) {
    if (c != ' ' && c != '\t' && num_spaces > 0) {
      /* output spaces and possible tabs */
      if (flag_expand
	  || (flag_initial && !in_initials)
	  || num_spaces == 1) {
	/* output spaces anyway */
	output_spaces(num_spaces);
	linelength += num_spaces;
	num_spaces = 0;
      }
      else
	while (num_spaces != 0) {
	  next_tab = get_next_tab(linelength);
	  if (next_tab > 0 && next_tab <= linelength + num_spaces) {
	    /* output a tab */
	    putchar('\t');
	    num_spaces -= (next_tab - linelength);
	    linelength = next_tab;
	  }
	  else {
	    /* output spaces */
	    output_spaces(num_spaces);
	    linelength += num_spaces;
	    num_spaces = 0;
	  }
	}
    }
    switch (c) {
    case ' ':               /* space */
      num_spaces++;
      break;
    case '\b':              /* backspace */
      /* preserve backspaces in output; decrement length for tabbing
       * purposes
       */
      putchar(c);
      if (linelength > 0)
	linelength--;
      break;
    case '\n':              /* newline */
      putchar(c);
      in_initials = 1;
      linelength = 0;
      break;
    case '\t':              /* tab */
      next_tab = get_next_tab(linelength + num_spaces);
      if (next_tab == 0) {
	while ((next_tab = get_next_tab(linelength)) != 0) {
	  /* output tabs */
	  putchar('\t');
	  num_spaces -= (next_tab - linelength);
	  linelength = next_tab;
	}
	/* output spaces */
	output_spaces(num_spaces);
	num_spaces = 0;
	putchar('\t');
	linelength += num_spaces + 1;
      }
      else
	num_spaces = next_tab - linelength;
      break;
    default:
      putchar(c);
      in_initials = 0;
      linelength++;
      break;
    }
  }
}

int main(int argc, char **argv)
{
  int i;
  FILE *fp;
  char *allocked_argvs = xmalloc(argc + 1);
  char **new_argv = xmalloc((argc + 1) * sizeof(char *));
  char *p;

  program_name = argv[0];
  memset(allocked_argvs, 0, argc + 1);
  for (i = 0; i < argc; i++) {
    p = argv[i];
    if (isdigit(p[1])) {
      new_argv[i] = xmalloc(strlen(p) + 2);
      sprintf(new_argv[i], "-t%s", p + 1);
      allocked_argvs[i] = 1;
    }
    else
      new_argv[i] = p;
  }
  new_argv[argc] = NULL;
  parse_args(argc, new_argv);
  if (optind == argc)
    tab(stdin);
  else {
    for (i = optind; i < argc; i++) {
      if (strcmp(argv[i], "-") == 0)
	fp = stdin;
      else {
	fp = fopen(argv[i], "r");
	if (fp == NULL) {
	  fprintf(stderr, "%s: can't open %s\n",
		  argv[0], argv[i]);
	  abort();
	}
      }
      tab(fp);
      if (fp != stdin)
	fclose(fp);
    }
  }
  /* free everything we can */
  for (i = 0; i < argc; i++)
    if (allocked_argvs[i])
      free(new_argv[i]);
  free(allocked_argvs);
  if (tab_stop_list != NULL)
    free(tab_stop_list);
  return EXIT_SUCCESS;
}

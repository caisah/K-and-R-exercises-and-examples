/* ATTENTION!!!
   This should not be compiled with -std=99 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>	/* flags for read and write */
#include <sys/types.h>	/* typedefs */
#include <sys/stat.h>	/* structure returned by stat */
#include "dirent.h"

void fsize(char *);

/* print file sizes */
main(int argc, char **argv)
{
  if( argc == 1 )	/* default: current directory */
    fsize(".");
  else
    while( --argc > 0 )
      fsize(*++argv);

  return  0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file "name" */
void fsize(char *name)
{
  struct stat stbuf;

  if( stat(name, &stbuf) == -1 ) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if( (stbuf.st_mode & S_IFMT) == S_IFDIR )
    dirwalk(name, fsize);
  printf("%8ld %s\n", stbuf.st_size, name);
}


#define	MAX_PATH	1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
  char name[MAX_PATH];
  Dirent *dp;
  DIR *dfd;

  if( (dfd = opendir(dir)) == NULL ) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while( (dp = readdir(dfd)) != NULL ) {
    if( strcmp(dp->name, ".") == 0
	||  strcmp(dp->name, "..") == 0
	)
      continue;	/* skip self and parent */
    if( strlen(dir) + strlen(dp->name) + 2 > sizeof(name) )
      fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
    else {
      sprintf(name, "%s/%s", dir, dp->name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}

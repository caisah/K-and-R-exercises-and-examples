#define NAME_MAX 14 // longest filename component;  system-dependent

typedef struct                // portable directory entry:
{
  long ino;                   // inode number
  char name[NAME_MAX+1];       // name + '\0' terminator
} Dirent;

typedef struct               // minimal DIR: no buffering, etc.
{
  int fd;                    // file descriptor for directory
  Dirent d;                  // the directory entry
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR * dfd);
void closedir(DIR *dfd);


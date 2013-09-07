/* Implement a simple version of the #define processor (i.e., no arguments) suitable
   for use with C programs, based on the routines of this section.
   You may also find getch and ungetch helpful. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 1000

/* nlist:  From K&R2 page 144.  Points to a search text and
 * a replacement text */
struct nlist
{
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int process(void);
int getch(void);
void ungetch(int);
int preproc(void);
int backslash(void);
int comment(void);
int literal(void);
int readword(void);

int main(void)
{
  int c;
  const int done = 0;     /* just a dummy for the infinite loop */
  int status = 1; /* 1 at line begin, 2 for failure, 0 otherwise */
	
  while(!done) {
    while(isspace(c = getch())) {
      putchar(c);
      if(c == '\n')
	status = 1;
    }
		
    if(c == '#' && status == 1)
      status = preproc();
		
    else if(c == '\\')
      status = backslash();
		
    else if(c == '/')
      status = comment();
		
    else if(c == '\"')
      status = literal();
		
    else if(c == EOF)
      return 0;
		
    else if(!isalpha(c) && c != '_') {
      putchar(c);
      status = 0;
    }
		
    else {
      ungetch(c);
      status = readword();
    }
		
    if(status == 2)
      return 1;
  }
  return 0;
} /* end main() */

/*
 * preproc:  Called when a '#' is found at the beginning of a line.
 * If a #define statement is found, it stores add the search and replacement
 * text to the hash table.  Otherwise it just prints what it reads.
 * The line a #define statement is found on is replaced with a blank line.
 */
int preproc(void)
{
  int c;
  char name[MAXWORD+1], defn[MAXWORD+1];
  char *n, *d;
	
  /* Read what comes after the '#' */
  for(n = name; isalpha(c = getch()) && n - name < MAXWORD; ++n)
    *n = c;
  *n = '\0';
	
  /* If it's a #define... */
  if(strcmp(name, "define") == 0) {
		
    /* ignore whitespace */
    while(isspace(c)) {
      if(c == '\n') { /* a #define followed by a '\n' is discarded */
	putchar(c);
	return 1;
      }
      c = getch();
    }
		
    /* Read search text */
    for(n = name; (isalnum(c) || c == '_') && n - name < MAXWORD; ++n) {
      *n = c;
      c = getch();
    }
    *n = '\0';
		
    /* Ignore whitespace */
    while(isspace(c)) {
      if(c == '\n')
	*defn = '\0'; /* If there is no replacement text. */
      c = getch();
    }
		
    /* Read replacement text. */
    for(d = defn; (isalnum(c) || c == '_') && d - defn < MAXWORD; ++d) {
      *d = c;
      c = getch();
    }
    *d = '\0';
		
    /* Add to hash table. */
    if(install(name, defn) == NULL)
      return 2;
  }
  else {                    /* not a #define statement */
    putchar('#');
    printf("%s", name);
  }
	
  /* finish line reading/printing line */
  while(c != '\n') {
    if(c == EOF)
      return EOF;
    putchar(c);
    c = getch();
  }
  putchar(c);
  return 1;
} /* end preproc() */

/*
 * backslash:  Makes sure that if a /, *, or " is preceded by a \ it is
 * just printed, not used in a comment or string literal.
 */
int backslash(void)
{
  int c, slash = 1;
  putchar('\\');
  while((c = getch()) == '\\') {
    slash = !slash;
    putchar(c);
  }
	
  if(slash)
    putchar(c);
  else
    ungetch(c);
	
  return 0;
} /* end backslash() */

/*
 * comment:  Prints comments without changes.
 */
int comment(void)
{
  int c;
  int after_star = 0;
	
  putchar('/');
	
  if((c = getch()) == '*') {   /* comment begin */
    putchar(c);
    c = getch();
		
    while(c != EOF) {
      if(c == '\\') {
	backslash();
	after_star = 0;
      }
      else if(c == '*') {
	after_star = 1;
	putchar(c);
      }
      else if(c == '/' && after_star) {
	putchar(c);
	return 0;
      }
      else {
	after_star = 0;
	putchar(c);
      }
      c = getch();
    }
		
    if(c == EOF)
      return EOF;
		
    putchar(c);
    return 0;
  }
  else {
    ungetch(c);
    return 0;
  }
} /* end comment() */

/*
 * literal:  Prints string literals without changes.
 */
int literal(void)
{
  int c;
  putchar('\"');
  c = getch();
	
  while(c != '\"' && c != EOF) {
    if(c == '\\')
      backslash();
    else
      putchar(c);
    c = getch();
  }
	
  if(c == EOF)
    return EOF;
	
  putchar(c);
  return 0;
} /* end literal() */

/*
 * readwood:  Reads an identifier and looks for it in the hash table.  If
 * it's found, it's replaced with the replacement text.  Otherwise, it is
 * printed as is.
 */
int readword(void)
{
  int c;
  char word[MAXWORD];
  char *w;
  struct nlist *node;
	
  c = getch();
  for(w = word; (isalnum(c) || c == '_') && c != EOF; ++w) {
    *w = c;
    c = getch();
  }
  *w = '\0';
  node = lookup(word);
  if(node == NULL)
    printf("%s", word);
  else
    printf("%s", node->defn);
	
  if(c == EOF)
    return EOF;
	
  ungetch(c);
  return 0;
} /* end readword() */

/***************************************************************************
 *                              From K&R2                                  *
 ***************************************************************************/

unsigned hash(char *);
char *strdup(char *);

/* lookup: From K&R2 page 145. Look for s in hashtab. */
struct nlist *lookup(char *s)
{
  struct nlist *np;
  for(np = hashtab[hash(s)]; np != NULL; np = np->next)
    if(strcmp(s, np->name) == 0)
      return np;
  return NULL;
}

/* install: From K&R2 page 145. Put (name, defn) in hashtab. */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;
	
  if((np = lookup(name)) == NULL) {
    np = (struct nlist *) malloc(sizeof(*np));
    if(np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else
    free((void *) np->defn);
  if((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

/* hash: From K&R2 page 144.  Form hash value for string s. */
unsigned hash(char *s)
{
  unsigned hashval;
  for(hashval = 0; *s != '\0'; ++s)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* strdup: From K&R2 page 143. Makes a duplicate of s. */
char *strdup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s) + 1);
  if(p != NULL)
    strcpy(p, s);
  return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch() */
int bufp = 0;       /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
  return;
}

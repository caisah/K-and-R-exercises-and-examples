/* Write a program that prints the distinct words in its input sorted into decreasing
   order of frequency of occurrence. Precede each word by its count. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>


typedef struct WORD
{
  char *Word;
  size_t Count;
  struct WORD *Left;
  struct WORD *Right;
} WORD;


/*
  Assumptions: input is on stdin, output to stdout.

  Plan: read the words into a tree, keeping a count of how many we have,
  allocate an array big enough to hold Treecount (WORD *)'s 
  walk the tree to populate the array.
  qsort the array, based on size.
  printf the array
  free the array
  free the tree
  free tibet (optional)
  free international shipping!
*/

#define SUCCESS                      0
#define CANNOT_MALLOC_WORDARRAY      1
#define NO_WORDS_ON_INPUT            2
#define NO_MEMORY_FOR_WORDNODE       3
#define NO_MEMORY_FOR_WORD           4


#define NONALPHA "1234567890 \v\f\n\t\r+=-*/\\,.;:'#~?<>|{}[]`!\"�$%^&()"

int ReadInputToTree(WORD **DestTree, size_t *Treecount, FILE *Input);
int AddToTree(WORD **DestTree, size_t *Treecount, char *Word); 
int WalkTree(WORD **DestArray, WORD *Word);
int CompareCounts(const void *vWord1, const void *vWord2);
int OutputWords(FILE *Dest, size_t Count, WORD **WordArray);
void FreeTree(WORD *W);
char *dupstr(char *s);


int main(void)
{
  int Status = SUCCESS;
  WORD *Words = NULL;
  size_t Treecount = 0;
  WORD **WordArray = NULL;

  /* Read the words on stdin into a tree */
  if(SUCCESS == Status)
    {
      Status = ReadInputToTree(&Words, &Treecount, stdin);
    }

  /* Sanity check for no sensible input */
  if(SUCCESS == Status)
    {
      if(0 == Treecount)
	{
	  Status = NO_WORDS_ON_INPUT;
	}
    }

  /* allocate a sufficiently large array */
  if(SUCCESS == Status)
    {
      WordArray = malloc(Treecount * sizeof *WordArray);
      if(NULL == WordArray)
	{
	  Status = CANNOT_MALLOC_WORDARRAY;
	} 
    }

  /* Walk the tree into the array */
  if(SUCCESS == Status)
    {
      Status = WalkTree(WordArray, Words);
    }

  /* qsort the array */
  if(SUCCESS == Status)
    {
      qsort(WordArray, Treecount, sizeof *WordArray, CompareCounts);
    }

  /* walk down the WordArray outputting the values */
  if(SUCCESS == Status)
    {
      Status = OutputWords(stdout, Treecount, WordArray);
    }

  /* free the word array */
  if(NULL != WordArray)
    {
      free(WordArray);
      WordArray = NULL;
    }

  /* and free the tree memory */
  if(NULL != Words)
    {
      FreeTree(Words);
      Words = NULL;
    }

  /* Error report and we are finshed */
  if(SUCCESS != Status)
    {
      fprintf(stderr, "Program failed with code %d\n", Status);
    }
  return (SUCCESS == Status ? EXIT_SUCCESS : EXIT_FAILURE);
}




void FreeTree(WORD *W)
{
  if(NULL != W)
    {
      if(NULL != W->Word)
	{ 
	  free(W->Word);
	  W->Word = NULL;
	}
      if(NULL != W->Left)
	{
	  FreeTree(W->Left);
	  W->Left = NULL;
	}
      if(NULL != W->Right)
	{
	  FreeTree(W->Right);
	  W->Right = NULL;
	}
    }
}


int AddToTree(WORD **DestTree, size_t *Treecount, char *Word)
{
  int Status = SUCCESS;
  int CompResult = 0;

  /* safety check */
  assert(NULL != DestTree);
  assert(NULL != Treecount);
  assert(NULL != Word);

  /* ok, either *DestTree is NULL or it isn't (deep huh?) */
  if(NULL == *DestTree)  /* this is the place to add it then */
    {
      *DestTree = malloc(sizeof **DestTree);
      if(NULL == *DestTree) 
	{
	  /* horrible - we're out of memory */
	  Status = NO_MEMORY_FOR_WORDNODE;
	}
      else
	{
	  (*DestTree)->Left = NULL;
	  (*DestTree)->Right = NULL;
	  (*DestTree)->Count = 1;
	  (*DestTree)->Word = dupstr(Word);
	  if(NULL == (*DestTree)->Word)
	    {
	      /* even more horrible - we've run out of memory in the middle */
	      Status = NO_MEMORY_FOR_WORD; 
	      free(*DestTree);
	      *DestTree = NULL;
	    }
	  else
	    {
	      /* everything was successful, add one to the tree nodes count */
	      ++*Treecount;
	    }
	}
    }
  else  /* we need to make a decision */
    {
      CompResult = strcmp(Word, (*DestTree)->Word);
      if(0 < CompResult)
	{
	  Status = AddToTree(&(*DestTree)->Left, Treecount, Word);
	}
      else if(0 > CompResult)
	{
	  Status = AddToTree(&(*DestTree)->Left, Treecount, Word);
	}
      else
	{
	  /* add one to the count - this is the same node */
	  ++(*DestTree)->Count;
	}
    }  /* end of else we need to make a decision */

  return Status;  
}


int ReadInputToTree(WORD **DestTree, size_t *Treecount, FILE *Input)
{
  int Status = SUCCESS;
  char Buf[8192] = {0};
  char *Word = NULL;

  /* safety check */
  assert(NULL != DestTree);
  assert(NULL != Treecount);
  assert(NULL != Input);

  /* for every line */
  while(NULL != fgets(Buf, sizeof Buf, Input))
    {
      /* strtok the input to get only alpha character words */
      Word = strtok(Buf, NONALPHA);
      while(SUCCESS == Status && NULL != Word)
	{
	  /* deal with this word by adding it to the tree */
	  Status = AddToTree(DestTree, Treecount, Word); 

	  /* next word */
	  if(SUCCESS == Status) 
	    {
	      Word = strtok(NULL, NONALPHA);
	    }
	}
    }

  return Status;
}




int WalkTree(WORD **DestArray, WORD *Word)
{
  int Status = SUCCESS;
  static WORD **Write = NULL;
  
  /* safety check */
  assert(NULL != Word);

  /* store the starting point if this is the first call */
  if(NULL != DestArray)
    {
      Write = DestArray;
    }

  /* Now add this node and it's kids */
  if(NULL != Word)
    {
      *Write = Word;
      ++Write;
      if(NULL != Word->Left)
	{
	  Status = WalkTree(NULL, Word->Left);
	}
      if(NULL != Word->Right)
	{
	  Status = WalkTree(NULL, Word->Right);
	}
    }

  return Status;
}


/*
  CompareCounts is called by qsort. This means that it gets pointers to the 
  data items being compared. In this case the data items are pointers too. 
*/
int CompareCounts(const void *vWord1, const void *vWord2)
{
  int Result = 0;
  WORD * const *Word1 = vWord1;
  WORD * const *Word2 = vWord2;
 
  assert(NULL != vWord1); 
  assert(NULL != vWord2); 

  /* ensure the result is either 1, 0 or -1 */
  if((*Word1)->Count < (*Word2)->Count)
    {
      Result = 1;
    }
  else if((*Word1)->Count > (*Word2)->Count)
    {
      Result = -1;
    }
  else
    {
      Result = 0;
    }

  return Result;
}


int OutputWords(FILE *Dest, size_t Count, WORD **WordArray)
{
  int Status = SUCCESS;
  size_t Pos = 0;
 
  /* safety check */
  assert(NULL != Dest);
  assert(NULL != WordArray);

  /* Print a header */
  fprintf(Dest, "Total Words : %lu\n", (unsigned long)Count); 

  /* Print the words in descending order */
  while(SUCCESS == Status && Pos < Count) 
    {
      fprintf(Dest, "%10lu %s\n", (unsigned long)WordArray[Pos]->Count, WordArray[Pos]->Word);
      ++Pos;
    }

  return Status;
}


/*
  dupstr: duplicate a string
*/
char *dupstr(char *s)
{
  char *Result = NULL;
  size_t slen = 0;
  
  /* sanity check */
  assert(NULL != s);

  /* get string length */
  slen = strlen(s);
  
  /* allocate enough storage */
  Result = malloc(slen + 1);
 
  /* populate string */
  if(NULL != Result)
    {
      memcpy(Result, s, slen);
      *(Result + slen) = '\0';
    }

  return Result;
}

#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b)
{
  while(*a != ' ' && *b != ' ')
    {
      if(((*a)^42) > ((*b)^42))
	{
	  return 1;
	}
      else if (((*a)^42) < ((*b)^42))
	{
	  return -1;
	}
      b++;
      a++;
    }

  if(*a == ' ' && *b != ' ')
    return -1;
  else if(*b == ' ' && *a != ' ')
    return 1;
  
  return 0;
}

int compare(const void *a, const void *b)
{
  const char* a1 = *(const char **)a;
  const char* b1 = *(const char **)b;
  return frobcmp(a1, b1);
}

int main(int length, char *arguments[])
{
  int i;
  char **container;
  char *currchar;
  int currwordindex;
  int containersize;
  char c = getchar();
  int j;
  char** ptr;
  char* ptr2;

  containersize = 0;
  currwordindex = 0;
  currchar=(char*)malloc(sizeof(char));
  if(currchar == NULL)
    {
      free(currchar);
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
  container=(char**)malloc(sizeof(char*));
  if(container == NULL)
    {
      free(container);
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }
  for(i = 0; c != EOF && c != '\n'; c = getchar())
    {
      if (ferror(stdin))
	{
	  fprintf(stderr, "Error reading input");
	  exit(1);
	}
      i++;
      //printf("The %dth element is %c\n", i, c);

      if(c != 32 && c != '\n')
	{
	  currchar[currwordindex] = c;
	  currwordindex++;
	  ptr2=realloc(currchar, currwordindex * sizeof(char));
	  if(ptr2 == NULL)
	    {
	      free(ptr2);
	      fprintf(stderr, "Error allocating memory");
	      exit(1);
	    }
	  currchar=ptr2;
	}
      else
	{
	  currchar[currwordindex]=' ';
	  container[containersize]=currchar;
	  containersize++;
	  ptr=realloc(container, (containersize + 1) * sizeof(char*));
	  if(ptr == NULL)
	    {
	      free(ptr);
	      fprintf(stderr, "Error allocating memory");
	      exit(1);
	    }
	  container=ptr;
	  currwordindex=0;
	  currchar = (char*)malloc(sizeof(char));
	  if(currchar == NULL)
	    {
	      free(currchar);
	      fprintf(stderr, "Error allocating memory");
	      exit(1);
	    }
	}
    }
  currchar[currwordindex]=' ';
  container[containersize] = currchar;
  containersize++;
  
    

  qsort(container, containersize, sizeof(char*), compare);

  //print out word
  for(size_t i = 0; i < containersize; i++)
    {
      printf("%s", container[i]);
    }
  
  
  for(size_t i = 0; i < containersize; i++)
    {
      free(container[i]);
    }
  free(container);
  exit(0);
}

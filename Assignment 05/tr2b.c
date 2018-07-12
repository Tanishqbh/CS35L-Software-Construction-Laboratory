#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc != 3)
    {
      fprintf(stderr, "Error: Incorrect number of arguments");
      exit(1);
    }

  char* arg1 = argv[1];
  char* arg2 = argv[2];

  while(*arg1 != '\0' && *arg2 != '\0')
    {      
      arg1++;
      arg2++;
    }

  if(*arg1 == '\0' && *arg2 != '\0')
    {
      fprintf(stderr, "Error: arguments are not the same length");
      exit(1); 
    }
  else if(*arg1 != '\0' && *arg2 == '\0')
    {
      fprintf(stderr, "Error: arguments are not the same length");
      exit(1); 
    }

  arg1 = argv[1];
  arg2 = argv[2];

  for(size_t i = 0 ; arg1[i] != '\0'; i++)
    for(size_t j = i + 1; arg1[j] != '\0'; j++)
      if(arg1[i] == arg1[j])
	{
	  fprintf(stderr, "Error: argument 1 has repeating characters");
	  exit(1);
	}

  char c = getchar();
  while(c != EOF)
    {
      arg1 = argv[1];
      size_t index = 0;
      size_t translated = 0;
      while(*arg1 != '\0')
	{
	  if(*arg1 == c)
	    {
	      translated = 1;
	      putchar(arg2[index]);
	      break;
	    }
	  index++;
	  arg1++;
	}
      if(!translated)
	{
	  putchar(c);
	}
      c = getchar();
    }
  putchar('\n');
  exit(0);
}

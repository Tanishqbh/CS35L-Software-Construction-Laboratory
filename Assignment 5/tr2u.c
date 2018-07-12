#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char* argerr = "Error: Incorrect number of arguments";
  char* lenerr = "Error: arguments are not the same length";
  char* reperr = "Error: argument 1 has repeating characters";

  if(argc != 3)
    {
      write(2, argerr, strlen(argerr));  
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
      write(2, lenerr, strlen(lenerr));
      exit(1); 
    }
  else if(*arg1 != '\0' && *arg2 == '\0')
    {
      write(2, lenerr, strlen(lenerr));
      exit(1); 
    }

  arg1 = argv[1];
  arg2 = argv[2];

  for(size_t i = 0 ; arg1[i] != '\0'; i++)
    for(size_t j = i + 1 ; arg1[j] != '\0'; j++)
      if(arg1[i] == arg1[j])
	{
	  write(2, reperr, strlen(reperr));
	  exit(1);
	}

  char buf[1];
  int c = read(0, buf, 1);
  while(c > 0)
    {
      arg1 = argv[1];
      size_t index = 0;
      size_t translated = 0;
      while(*arg1 != '\0')
	{
	  if(*arg1 == buf[0])
	    {
	      translated = 1;
	      buf[0] = arg2[index];
	      write(1, buf, 1);
	      break;
	    }
	  index++;
	  arg1++;
	}
      if(!translated)
	{
	  write(1, buf, 1);
	}
      c = read(0, buf, 1);
    }
  buf[0] = '\n';
  write(1, buf, 1);
  exit(0);
}

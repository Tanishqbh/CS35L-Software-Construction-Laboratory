#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int foption = 0;

int frobcmp(char const *a, char const *b)
{
  if(foption)
    {
      unsigned char const* a1 = a;
      unsigned char const* b1 = b;
      while(*a1 != ' ' && *b1 != ' ')
	{
	  if(toupper((*a1)^42) > toupper((*b1)^42))
	    {
	      return 1;
	    }
	  else if (toupper((*a1)^42) < toupper((*b1)^42))
	    {
	      return -1;
	    }
	  b1++;
	  a1++;
	}
    }
  else
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

int main(int argc, char* argv[])
{
  //error messagees
  char* openerr = "Error: file could not be opened";
  char* fstaterr = "Error: fstat error";
  char* readerr = "Error: input could not be read";
  char* argerr = "Error: wrong number of arguments";
  
  int containersize;
  struct stat fileStat;
  char buf[1];
  int fp;
  char **container;
  int initialsize;
  int readstdin = 0;
  char* filestring;
  
  if(argc ==2)
    {
      if(argv[1][0] == '-')
	readstdin = 1;
    }
  else if(argc == 1)
    {
      readstdin = 1;
    }
  
  //read from file
  if(!readstdin)
    {
      if(argc == 2)
	{
	  fp = open(argv[1], O_RDONLY);
	}
      else if(argc == 3)
	{
	  fp = open(argv[2], O_RDONLY);
	  if(argv[1][0] == '-' && argv[1][1] == 'f')
	    foption = 1;
	}
      else
	{
	  write(2, argerr, strlen(argerr));
	  exit(1);
	}
      
      if (fp < 0)
	{
	  write(2, openerr, strlen(openerr));
	  exit(1);
	}

      if(fstat(fp, &fileStat) < 0)
	{
	  write(2, fstaterr, strlen(fstaterr));
	  exit(1);
	}
      
      size_t iterations = 0;
      do
	{
	  //if the file changes size, clear the current container
	  if(iterations > 0)
	    {
	      free(container);
	      free(filestring);
	    }
	    
	  iterations++;
	  initialsize = fileStat.st_size;
	  filestring = (char*)malloc((fileStat.st_size + 1) * sizeof(char));
      
	  if(read(fp, filestring, fileStat.st_size) <= 0)
	    {
	      write(2, readerr, strlen(readerr));
	      exit(1);
	    }
	  //filestring[strlen(filestring)] = ' ';
	  //parse filestring and put into container      
	  size_t count = 0;
	  for(size_t j = 0; filestring[j] != '\0'; j++)
	    {
	      //if(j == fileStat.st_size - 1)
	      //{
	      //filestring[j] = ' ';
	      //}
	  
	      if(filestring[j] == ' ')
		{
		  count++;
		}
	    }

	  container = (char**)malloc(count * sizeof(char*));

	  containersize = 0;
	  container[containersize] = &filestring[0];
	  containersize++;
	  for(size_t i = 0; filestring[i] != '\0'; i++)
	    {
	      if(filestring[i] == ' ')
		{
		  container[containersize] = &filestring[i + 1];
		  containersize++;
		}
	    }
	  
	  if(fstat(fp, &fileStat) < 0)
	    {
	      write(2, fstaterr, strlen(fstaterr));
	      exit(1);
	    }
	} while (initialsize != fileStat.st_size);
      
    }
  else
    //read from stdin
    {
      char c = read(0, buf, 1);
      if(c < 0)
	{
	  write(2, readerr, strlen(readerr));
	  exit(1);
	}
      size_t currwordindex = 0;
      containersize = 0;
      container = (char**)malloc(sizeof(char**));
      container[0] = (char*)malloc(sizeof(char*));

      char** ptr1;
      char* ptr2;

      while(buf[0] != '\n') 
	{
	  ptr2 = realloc(container[containersize], (currwordindex + 1) * sizeof(char*));
	  container[containersize] = ptr2;
	  container[containersize][currwordindex] = buf[0];
	  currwordindex++;

	  if(buf[0] == ' ' || buf[0] == '\0' || buf[0] == '\n')
	    {
	      
	      containersize++;
	      ptr1 = realloc(container, ((containersize + 1) * sizeof(char**)));
	      container = ptr1;
	      currwordindex = 0;
	    }	  
	  if(read(0, buf, 1) < 0)
	    {
	      write(2, readerr, strlen(readerr));
	      exit(1);
	    }
	}
      containersize++;
    }

  
      qsort(container, containersize, sizeof(char*), compare); 
      
      //write
      for(size_t i = 0; i < containersize; i++)
	{
	  for(size_t j = 0; container[i][j] != ' ' && container[i][j] != '\0'; j++)
	    {
	      buf[0] = container[i][j];
	      write(1, buf, 1);
	    }
	  buf[0] = '\n';
	  write(1, buf, 1);
	}

      exit(0);
}

#include <stdio.h>
#include <stdlib.h>   // Necessary for exit()
#include "backend.h"
#include "path.h"

#define WELCOME_MESSAGE "Welcome to Ladders!\n"
#define START_PROMPT "Starting word: "
#define GOAL_PROMPT  "    Goal word: "

int prompt_word(char *, char *);

int main()
{
  char start[5], goal[5];

  init();

  printf(WELCOME_MESSAGE);

  while (1) {
    printf("\n");  
    while (prompt_word(START_PROMPT, start) != 0 ) 
      printf("(Please type five lowercase letters and RETURN.)\n");
    while (prompt_word(GOAL_PROMPT, goal) != 0 ) 
      printf("(Please type five lowercase letters and RETURN.)\n");
    find_path(start, goal);
  }
}



int prompt_word(char *s, char *p)
{

  char *q;
  char c;

  while (1) {
    printf("%s", s);
    fflush(stdout);
    q=p;
    while (1) {
      c=getchar();
      if (c==EOF)
	exit(-1);            // Should let exit() take care of the sudden EOF.
      if (c=='\n')
	break;
      if (q<p+5)
	*q=c;
      q++;
    }
    if (q==p+5)   // read exactly five-letter word
      return 0;   // got a good word //
    else
      return 1;   // just a <return>  //
  }
}



#include <stdio.h>
#include <stdlib.h>   // Necessary for exit()
#include "backend.h"     

#define WELCOME_MESSAGE "Welcome to Ladders!\n"
#define START_PROMPT "Starting word: "
#define GOAL_PROMPT  "    Goal word: "

int prompt_word(char *, char *);

int main()
{
  char start[5], goal[5];

  init();

 /* printf(WELCOME_MESSAGE);

  while (1) {
    printf("\n");  
    while (prompt_word(START_PROMPT, start) != 0 ) 
      printf("(Please type five lowercase letters and RETURN.)\n");
    while (prompt_word(GOAL_PROMPT, goal) != 0 ) 
      printf("(Please type five lowercase letters and RETURN.)\n");
    find_path(start, goal);
  }*/
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




/********* test

int main()
{
  init_data();

  print_word(0); printf("\n");
  print_word(1); printf("\n");
  print_word(5755); printf("\n");
  print_word(5756); printf("\n");

  init_adj_mat();

  //Want to see the density.
  int i,j,d=0;
  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      d+=adj_mat[i][j];
  printf("The density is %d.\n", d);

  // Here starts the command line loop.
  
}

**********/

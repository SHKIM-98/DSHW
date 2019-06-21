#include <stdio.h>
#include <stdlib.h>   // Necessary for exit()
#include "backend-bst.h"     

#define WELCOME_MESSAGE "Welcome to Address Book!\n"
#define COMMAND_PROMPT "ADDR>"
#define ADD_PROMPT "ADD NAME>>"
#define SEARCH_PROMPT "SEARCH NAME>>"
#define NUMBER_PROMPT "ENTER NUMBER>>>"
#define DELETE_PROMPT "DELETE NAME>>"
#define PROMPT_FILE "ENTER INPUT FILE NAME>>"
#define INPUT_FILE_NAME_LENGTH 20   // file name of at most 20 characters.

int n;  // the number of records

int prompt_command(char *, char *);
int prompt_name(char *, char *);
int prompt_number(char *, char *);
int prompt_file_name(char *, char *);

int main()
{
  char command[1];
  char name[3], number[4];
  char input_file_name[INPUT_FILE_NAME_LENGTH]; 
  FILE *input_file;  // file pointer for formatted input file.

  init_pool();
  
  printf(WELCOME_MESSAGE);

  while (1) {
  restart:
    if (prompt_command(COMMAND_PROMPT, command) != 0)
      goto restart;
    switch (command[0]) {
    case 'A':
    case 'a':
      if (prompt_name(ADD_PROMPT, name) !=0)
	goto restart;
      if (prompt_number(NUMBER_PROMPT, number) !=0)
	goto restart;
      add(name, number);
      break;
    case 'S':
    case 's':
      if (prompt_name(SEARCH_PROMPT, name) !=0)
	goto restart;
      search(name);
      break;
    case 'D':
    case 'd':
       if (prompt_name(DELETE_PROMPT, name) !=0)
	goto restart;
      delete(name);
      break;
    case 'Q':
    case 'q':
      printf("Quitting ... \n");
      return 0;
    case 'P':
    case 'p':
      print_list();
      break;
    case 'H':
    case 'h':
      print_height();
      break;
    default:
      printf("Please enter a valid command.\n");
      goto restart;
    }
  }
}


int prompt_command(char *s, char *p)
{

  char *q;
  char c;

  while (1) {
    printf("%s ", s);
    fflush(stdout);
    q=p;
    while (1) {
      c=getchar();
      if (c==EOF)
	exit(-1);      // Should let exit() take care of the sudden EOF.
      if (c=='\n')     
	break;
      if (q<p+1)
	*q=c;
      q++;
    }
    if (q==p+1)
      return 0;   // got a good command //
    if (q==p)
      return 1;   // just a <return>  //
    printf("Please type a command.\n");
  }
}


int prompt_name(char *s, char *p)
{

  char *q;
  char c;

  while (1) {
    printf("%s ", s);
    fflush(stdout);
    q=p;
    while (1) {
      c=getchar();
      if (c==EOF)
	exit(-1);      // Should let exit() take care of the sudden EOF.
      if (c=='\n')
	break;
      if (q<p+3)
	*q=c;
      q++;
    }
    if (q==p+3)
      return 0;   // got a good name //
    if (q==p)
      return 1;   // just a <return>  //
    printf("Please type a three-letter name.\n");
  }
}


int prompt_number(char *s, char *p)
{
  char *q;
  char c;

  while (1) {
    printf("%s ", s);
    fflush(stdout);
    q=p;
    while (1) {
      c=getchar();
      if (c==EOF)
	exit(-1);            // Should let exit() take care of the sudden EOF.
      if (c=='\n')
	break;
      if (q<p+4)
	*q=c;
      q++;
    }
    if (q==p+4)
      return 0;   // got a good number //
    if (q==p)
      return 1;   // just a <return>  //
    printf("Please type a four-digit number.\n");
  }
  return 0;
}


// Prompt for input file name and just check the length
int prompt_file_name(char *s, char *p)
{
  char *q;
  char c;
  const int l = INPUT_FILE_NAME_LENGTH;

  while (1) {
    printf("%s ", s);
    fflush(stdout);
    q=p;
    while (1) {
      c=getchar();
      if (c==EOF)
	exit(-1);            // Should let exit() take care of the sudden EOF.
      if (c=='\n')
	break;
      if (q<p+l)
	*q=c;
      q++;
    }
    if (q<=p+l)
      return 0;   // got a file name //
    if (q==p)
      return 1;   // just a <return>  //
    printf("Please type a file name in 20 letter.\n");
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "backend.h"

/***** Programming Homework 6 ***********
Implement Breadth-First Search on the graph constructed in "backend.c" and use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via "backend.h"
*****************************************/
int BFS(int,int);
void print_path(int,int);

void find_path(char start[5], char goal[5])
{
  int i,j,k;
  
  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else {
    k = BFS(i,j); 
    if( k == 1 )
    {
	    print_path(i,j);
    }
    else  
    {
      printf("Sorry. There is no path from ");
      print_word(i);
      printf(" to ");
      print_word(j);
      printf("\n");
    } 
  }
}

int STATE[N];   // 1: UNDISCOVERD
                // 2: DISCOVERD
                // 3: PROCEED
            
void init_STATE()       //Initialize STATE
{
  int i;
  for(i=0; i<N; i++)
  {
    STATE[i] = 1;
  }
}

int parent[N];

void init_parent()      //Initialize parent
{
  int i;
  for(i=0; i<N; i++)
  {
    parent[i] = -1;
  }
}

//========================  Make Queue  ============================= //
struct node * Queue = NULL;       

void push(int n)
{
  struct node * p;
  struct node * q;
  q = malloc(sizeof(struct node *));
  q -> index = n;
  
  if( Queue == NULL )
  {
    Queue = q;
    q -> next = NULL;
  }
  else
  {
    p = Queue;
    q -> next = p;
    Queue = q;
  }
}

int pop()
{
  struct node * p;
  struct node * q;
  int i;
  p = Queue;
  if(p -> next == NULL)
  {
    i = p -> index;
    Queue = NULL;
    free(p);
    return i;
  }
  else
  {
    while (p-> next != NULL)
    {
      q = p;
      p = p-> next;
    }
    i = p -> index;
    q -> next = NULL;
    free(p);    
    return i;
  }
}
// ==================== Make Stack ============================ //

struct node * Stack = NULL;

void stack_push(int x)
{
    struct node * p;
    struct node * q;
    q = malloc(sizeof(struct node *));
    q -> index = x;

    if(Stack == NULL)
    {
        Stack = q;
        q -> next = NULL;
    }
    else
    {	
	    p = Stack;
        q -> next = p;
        Stack = q;
    }
}

int stack_pop()
{
    struct node * p;
    int i;

    if(Stack->next == NULL)
    {
        p = Stack;
        i = p -> index;
        free(p);
        Stack = NULL;
        return i;
    }
    else
    {
        p = Stack;
        i = p-> index;
        Stack = p->next;
        free(p);
        return i;
    }
}

// ==================== Operate BFS =========================== //

int BFS(int i, int j)
{
  struct node * p;
  int current;
  Queue = NULL;
  init_STATE();
  init_parent();
  STATE[i] = 2;
  push(i); 
 
  while (Queue != NULL)
  {
    current = pop();
    p = adj_list[current];
    while (p != NULL)
    {
      if(STATE[p->index] == 1)
      { 
        parent[p->index] = current;
        push(p->index);
        STATE[p->index] = 2;
        if(p->index == j)
        {
          return 1;
        }  
      }
      p = p-> next;
    }
    STATE[current] = 3;
  } 
  return -1;
}

void print_path(int i,int j)
{
  Stack = NULL;
  int k = j;
  while( k != -1 )
  {
    stack_push(k);
    k = parent[k];
  }

  struct node * p;
  int num = 0;

  p = Stack;
  while( p!= NULL )
  {
    printf("\t%d ",num);
    print_word(stack_pop());
    printf("\n");
    p = p-> next;
    num++;
  }

}


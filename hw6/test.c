#include <stdio.h>
#include <stdlib.h>

struct node {
    int index;
    struct node * next;
};

struct node * Queue;

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
    printf("%d\t",i);
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
    printf("%d\t",i);
    q -> next = NULL;
    free(p);
    return i;
  }
}

void main()
{
  while(1)
  {
    struct node * p;
    int m,n,i;
    printf("Insert Number (1: push  2: pop  3: print  0: quit  ----  ");
    scanf("%d",&m);
    if( m == 0)
      break;
    switch(m)
    {
      case 1:
          printf("PUSH : ");
          scanf("%d",&n);
          push(n);
          break;
      case 2:
          printf("POP\n");
          i = pop();
          printf("%d\t",i);
          break;
      case 3:
          p = Queue;
          while (p != NULL)
          {
            printf("%d ",p->index);
            p = p-> next;
          }
          break;
    }
  }
  
}
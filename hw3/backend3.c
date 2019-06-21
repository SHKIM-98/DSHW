#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend3.h"     

#define POOL_SIZE 5

// pool of memory
struct record pool[POOL_SIZE];
struct record * top=pool;  // pool is constant.  We need a pointer variable for stack top.


// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init_pool() // Initialize the pool
{
  int i;
  struct record *r=pool;
  struct record *s;

  pool[POOL_SIZE-1].next=NULL;  

  for(i=1;i<POOL_SIZE;i++) { 
    s=r++;
    s->next=r;
  }
}


// Get a node from the pool.  Exit if pool is empty.
struct record * new_node()  
{
	struct record * r;
  
	if(top==NULL)
	{
		printf("Pool is empty. Bye!\n");
		exit(0);
	}

	r=top;
	top=r->next;  
	return r;
  
  // Error Message for OVERFLOW:  printf("Pool is empty. Bye!\n");
  // Your program quits with "exit(0)", if OVERFLOW occurs.
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->next=top;
  top=r;
}


void add(char *name, char *number)
{
	struct record * p;
	struct record * q;
	struct record * r;
	int result;
	q = new_node();
	q -> name[0] = name[0];
	q -> name[1] = name[1];
	q -> name[2] = name[2];
	q -> number[0] = number[0];
	q -> number[1] = number[1];
	q -> number[2] = number[2];
	q -> number[3] = number[3];
	
	p = data;
	while( p != NULL && (result = compare(name,p)) > 0 )
	{	
		r = p;
		p = p -> next;
	}

	if(  p == NULL || result < 0 )
	{	
		if( p == data )
		{
			data = q;
			q -> next = p;
		}
		else
		{
			r -> next = q;
			q -> next = p;
		}	
	}
	else
	{
		printf("Can't add.  The name already exists!\n");
	}

  // Error Message for duplicate name
  // printf("Can't add.  The name already exists!\n");
}


void search(char name[3])  
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))>0)
    r=r->next;
  if(r==NULL || result<0)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
	struct record * p;
	struct record * q;

	p = data;
	
	while( p!=NULL && compare(name,p) != 0 )
	{
		q = p;
		p = p-> next;	
	}

	if( p == NULL )
	{
		printf("Couldn't find the name. \n");
	}
	else
	{
		if ( p == data )
		{
			data = p-> next;
			free_node(p); 
		}
		else
		{
			q -> next = p -> next;
			free_node(p);
		}
		printf("The name was deleted.\n");
	}
}


/* Just a wrapper of strncmp(), except for the case r is NULL. 
 Negative value if key is less than r.
​0​ if key and r are equal.
 Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)  
    return -1;
  else
    return strncmp(key, r->name, 3);
}

// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
	struct record * p;
	p = data;

	while (p != NULL)
	{
		print_name(p);
		printf(" : ");
		print_number(p);
		printf("\n");
		p = p-> next;
	}
}


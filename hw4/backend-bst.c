#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"     

#define POOL_SIZE 10

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * left;
  struct record * right;
};

void print_name(struct record *);
void print_number(struct record *);

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record * top=pool;  // a pointer variable for pool stack top.

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init_pool() // Initialize the pool; Use right instead of next!!!
{
  int i;
  struct record *r=pool;
  struct record *s;

  pool[POOL_SIZE-1].right=NULL;  

  for(i=1;i<POOL_SIZE;i++) {  
    s=r++;
    s->right=r;
  }
}

// Get a node from the pool. Returns NULL if pool is empty. (A BETTER DESIGN)
// When calling new(), make sure to check if it is NULL. 
struct record * new_node()  
{
  struct record *r;
  
  if(top==NULL) 
	return NULL;
    
  r=top;
  top=r->right;  // Again, right instead of next.
  return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->right=top;  // Again, right instead of next.
  top=r;
}


/***********************
Address Book by binary search tree
**************************/

void search(char name[3])  
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
	struct record * p;
	struct record * q;
	struct record * r;
	int i;	
	q = new_node();
	if(q == NULL) 
	{	
		printf("Can't add.  The pool is empty!\n");
		return ;
	}
	q->name[0] = name[0];
	q->name[1] = name[1];
	q->name[2] = name[2];
	q->number[0] = number[0];	
	q->number[1] = number[1];	
	q->number[2] = number[2];	
	q->number[3] = number[3];
	q->left = NULL;
	q->right = NULL;
		
	if(data == NULL)
	{	
		data = q;
	}
	else
	{
		p = data;
		while(p !=NULL)
		{
			if((i=compare(q->name,p))==0)
			{
  				printf("Can't add.  The name already exists!\n");
				return ;
			}
			else if((i=compare(q->name,p))<0)
			{
				r = p;
				p = p->left;
			}
			else
			{
				r = p;
				p = p->right;
			}
		}
		
		if(compare(q->name,r)<0)
		{
			r->left = q;
		}
		else
		{
			r->right =q;
		}
	}
	printf("The name was successfully added!\n");
	return ;	
		
		
  // Messages to print
  //  printf("Can't add.  The name already exists!\n");
  //  printf("Can't add.  The pool is empty!\n");
  //  printf("The name was successfully added!\n");
}


// The most complicated.
void delete(char name[3])
{
	struct record * p;
	struct record * q;
	struct record * r;
	struct record * r_parent;
	p = data;
	
	while(p != NULL && compare(name,p) !=0)
	{
		if( compare(name,p)<0)
		{
			q = p;
			p = p->left;
		}
		else
		{
			q = p;
			p = p->right;
		}
	}
	
	if(p == NULL)
	{	
  		printf("Couldn't find the name.\n");
		return ;
	}

	if( p->left ==NULL && p->right == NULL)	/* p have no child */
	{
	 	if( p  == data )	/* if p = root node */
		{	
			data = NULL;
			free_node(p);
			return;
		}
		
		if( q->left == p)
		{
			q -> left = NULL;
		}
		else
		{
			q->right = NULL;
		}
		free_node(p);
		return;
	}	
	else if( p->left !=NULL && p->right !=NULL)	/* p have two childs */
	{
		
		r_parent = p;
		r = p -> right;
		while( r-> left != NULL)
		{
			r_parent = r;
			r = r -> left;
		}
		
		if( p == data )		/* if p == root node */
		{	
			
			if( r_parent == p )
			{
				if( r-> right == NULL )
				{
					p -> right = NULL;
				}
				else
				{
					p -> right = r-> right;
				}
				r -> left = p -> left;
				r -> right = p -> right;	
			}
			else
			{	if( r-> right == NULL )
				{
					r_parent-> left  = NULL;
				}
				else 
				{
					r_parent -> left  = r-> right;
				}

				r -> left = p ->left;
				r -> right = p ->right;
		
			}
			free_node(p);
			data = r;
			return;
		}
		
			
		if( r_parent == p )
		{
			if( r-> right == NULL )
			{
				p -> right = NULL;
			}
			else
			{
				p -> right = r-> right;
			}
			r -> left = p -> left;
			r -> right = p -> right;	
		}
		else
		{	if( r-> right == NULL )
			{
				r_parent ->left = NULL;
			}
			else 
			{
				r_parent ->left = r-> right;
			}

			r -> left = p ->left;
			r -> right = p ->right;
		
		}
		
		if( q-> left == p)
		{
			q -> left = r;
		}
		else
		{
			q-> right = r;
	
		}	

		free_node(p);
	}
	else 	/* p has one child */
	{
		if ( p == data )		/* if p == root node */
		{
			if( p -> left == NULL )
			{
				data = p -> right;
				free_node(p);
				return ;
			}
			else
			{
				data = p -> left;
				free_node(p);
				return ;
			}
		}
		
		if( q->left == p )
		{
			if( p->left == NULL)
			{
				q -> left = p -> right;
			}
			else
			{
				q -> left = p -> left;
			}
		}
		else	
		{
			if( p->right == NULL)
			{
				q -> right = p -> left;
			}
			else
			{
				q-> right = p -> right;
			}
		}
		free_node(p);
	}
	printf("The name was deleted.\n");  
  // Messages to print
  //  printf("The name was deleted.\n");  
  //  printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
	struct record * p;
	p = t;


	if(p !=NULL)
	{	
		print_inorder(p->left);
		print_name(p);
		printf(" : ");
		print_number(p);
		printf("\n");
		print_inorder(p->right);
	}
}

void print_list()  
{
  print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t)
{
	struct record * p;
	p = t;
	if ( p  == NULL )	{ return -1; }
	else
	{	
		int lb = height( p -> left);
		int rb = height( p -> right);
		if (lb < rb)
		{
			return rb+1;
		}
		else
		{
			return lb+1;
		}	
	}
// dummy return.  Should return a valid height.
}

void print_height()  
{
  printf("The Address Book BST's height is %d.\n", height(data));
}

/*
 Data Structure programming assignment.  The same address book program with hashing with chaining.

Will take a hash prime p, not too big, probably 17, for an easy test.

Give a function name_to_num().

Define the hash function hash(name)= name_to_num(name) mod p. 


The list of first three hundred primes:

{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, \
67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, \
139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, \
223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, \
293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, \
383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, \
463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, \
569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, \
647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, \
743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, \
839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, \
941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, \
1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, \
1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, \
1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, \
1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, \
1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, \
1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, \
1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, \
1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, \
1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, \
1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, \
1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, \
1931, 1933, 1949, 1951, 1973, 1979, 1987}

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-hash.h"

#define HASH_PRIME 17
#define POOL_SIZE 100

int name_to_num(char name[3])
{
  int x;

  x=name[0];
  x=x<<8;
  x=x+name[1];
  x=x<<8;
  return x+name[2];
}

int hash(char name[3])
{
  return name_to_num(name)%HASH_PRIME;
}
/* "abc" and "bbb" have the same hash value.  So do abt and bbs. */ 


// record structure
struct record {
  char name[3];
  char number[4];
  struct record * next;
};

// pool of memory
struct record pool[POOL_SIZE];
struct record * top=pool;  // a pointer variable for stack top.

// utility function declarations
int compare(char key[3], struct record *);
void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);
  
// Hash table: an array of hash values.  
struct record * hash_table[HASH_PRIME];

// Initially, each pointer of the hash table is valued NULL.
void init_hash_table()
{
  int i;
  
  for(i=0;i<HASH_PRIME;i++)
    hash_table[i]=NULL;
}

// Printing all the addresses does not make a good sense in hashing...


// Still use the same memory management.
void init_pool() // Initialize the pool. 
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


void init()
{
  init_pool();
  init_hash_table();
}


// Get a node from the pool. Returns NULL if pool is empty. (A BETTER DESIGN)
// When calling new(), make sure to check if it is NULL. 
struct record * new_node()  
{
  struct record *r;
  
  if(top==NULL)
    return NULL;

  r=top;
  top=r->next;  
  return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->next=top;  
  top=r;
}

/**************************
IMPORTANT NOTE on add()
 1. Allow duplicate names.
 2. Put in front of the linked list.
**************************/
void add(char *name, char *number)
{
	int hh=hash(name);
	struct record *r=hash_table[hh];

	struct record *p;
 
	p = new_node();
	if( p == NULL )
	{
		printf("Can't add. The pool is empty!\n");
		return ;
	}
	
	p -> name[0] = name[0];
	p -> name[1] = name[1];
	p -> name[2] = name[2];
	p -> number[0] = number[0];
	p -> number[1] = number[1];
	p -> number[2] = number[2];
	p -> number[3] = number[3];

	if( r == NULL )
	{
		p -> next = NULL;
		r = p;
	}
	else
	{
		p -> next = r;
		r = p;
	}
 	printf("The name was successfully added!\n");
  	
	hash_table[hh] = r;
	

	return ;
  // Messages to print
  //  printf("Can't add.  The pool is empty!\n");
  //  printf("The name was successfully added!\n");
}
  
/**************************
IMPORTANT NOTE on search()
Because we allow duplicate names, search() finds the most recently-added name.
Prints the number of comparisons.
**************************/
void search(char name[3])  
{
	struct record *r=hash_table[hash(name)];
	struct record *p;
	int cmp = 0;		 				/* the number of key comparisons */
	
	p = r;
	while (p != NULL)
	{
		if(compare(name,p) == 0)
		{
			cmp ++;
			break;
		}
		p = p->next;
		cmp++;
	}

	if( p == NULL )
	{
		printf("Couldn't find the name\n");
	}
	else
	{
		print_name(p);
		printf(" : ");
		print_number(p);
		printf(" was found\n ");
	}
	
	printf("%d key comparisons were made\n", cmp); 
  	return ;
  
  // Messages to print
  //   printf("Couldn't find the name.\n");
}

/**************************
IMPORTANT NOTE on delete()
Because we allow duplicate names, delete() removes the most recently-added name.
Prints the number of comparisons.
**************************/
void delete(char name[3])
{
	struct record *r, *p, *q;
	int cmp = 0;
	r=hash_table[hash(name)];

	p = r;
	q = p;
	
  	
	while (p != NULL)
	{
		if( compare(name,p) == 0)
		{
			cmp++;
			break;
		}

		q = p;
		p = p->next;
		cmp++;
	}

	if( p == NULL )
	{
		printf("Couldn't find the name\n");
	}
	else
	{
		if ( p == r)
		{
			r = p->next;
			free_node(p);
		}
		else
		{
			q-> next = p ->next;
			free_node(p);
		}
	printf("The name was successfully deleted!\n");
	}
	
	hash_table[hash(name)] = r;

	printf("%d key comparisons were made\n", cmp); 

	

	return ;

	
  // Messages to print
  //   printf("Couldn't find the name.\n");
  //   printf("The name was successfully deleted!\n");
}

/* Just a wrapper of strncmp().
 Negative value if key is less than r.
​0​ if key and r are equal.
 Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_name(struct record *r)
{
  print_data(r->name, 3);
}

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


/*
  These are the collection of structs that are used throughout the whole program
  Structures provide a way to group a set of related 
    variables of diverse types into a single unit of memory. 

  The structure as a whole can be referenced by a single name or pointer; 
    the structure members can be accessed individually too. 

  Structures can be passed to functions and returned from functions. 
  They are defined using the keyword `struct`

  Combining `typedef` with `struct` can make code clearer. 

  When you have a variable containing a struct, you can access its fields using the dot operator (.).
  If you have a pointer to a struct, You have to use the arrow operator (->) to access its fields. 
 */

typedef struct order Order;     // For Orders categories
typedef struct receipt Receipt; // For Sales Receipt

struct order
{
  char code[5];
  char name[100];
  float price;
};

struct receipt
{
  struct order;
  unsigned int quantity;
  float amount;
};
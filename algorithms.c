/*
 * HAOUCHE ACHOUR 
 * GROUPE TP1A
 */
#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
 * Create an empty array
 * @param struct array *self
 */
void array_create(struct array *self)
{
  self->capacity = 0;
  self->size = 0;
  self->data = NULL;
}

/*
 * Create an array with initial content
 * @param struct array *self
 * @param const int *other
 * @param size_t size
 */
void array_create_from(struct array *self, const int *other, size_t size)
{
//--init capacity, size and alloued *data.
  self->capacity = size;
  self->size = size;
  self->data = calloc(self->capacity,sizeof(self->data));
//--put *other in *data.
  for(size_t i = 0; i < size ; i++) self->data[i] = other[i];
}

/*
 * Destroy an array
 * @param struct array *self
 */
void array_destroy(struct array *self) 
{
//--to destroy we init size and capacity to zero and we free data.
  self->capacity = 0;
  self->size = 0;
  free(self->data);
}

/*
 * Tell if the array is empty
 * @param const struct array *self
 */
bool array_empty(const struct array *self) 
{
//--is not empty if size or capacity different of zero or data is null.
  if(self->size == 0 || self->capacity == 0 || !self->data)  return true;
  return false;
}

/*
 * Get the size of the array
 * @param const struct array *self
 * @return size_t 
 */
size_t array_size(const struct array *self) 
{
  return self->size;
}

/*
 * Compare the array to another array (content and size)
 * @param const struct array *self
 * @param const struct int *content
 * @param size_t size
 * @return bool
 */
bool array_equals(const struct array *self, const int *content, size_t size) 
{
//--if the size not equal.
  if(array_size(self) != size)  return false;
//--if one of then or the tow is empty.
  if(array_empty(self) == true || content == NULL)  return false;
//--test all data are equal.
   for(size_t i = 0; i < size ; i++)
    {
      if(self->data[i] != content[i]) return false;
    }
  return true;
}

/*
 * grow the capacity of the array
 * @param struct array *self
 */
void array_grow(struct array *self)
{
//--if is an empty array
assert(array_empty(self) == false);
//--init a new capacity and *data,(copy self.data)and(init self.data and capacity).
  size_t capacity = self->capacity*2;
  int *data = calloc(capacity,sizeof(int));
  memcpy(data,self->data,self->size*sizeof(int));
  free(self->data);
  self->data = data;
  self->capacity = capacity;
}

/*
 * Add an element at the end of the array
 * @param struct array *self
 * @param int data
 */
void array_push_back(struct array *self, int data) 
{
  //--if self is empty alloc and push like the first element of array
  if(array_empty(self))
  {
    self->capacity = 1;
    self->data = calloc(2,sizeof(int));
    self->data[0] = data;
    self->size++;
  }
  else
  {
    //--if the capacity is more than size (array is full).
    if(self->capacity <= array_size(self))  array_grow(self);
    self->data[self->size] = data;
    self->size++;
  }
}

/*
 * Remove the element at the end of the array
 * @param struct array *self
 */
void array_pop_back(struct array *self) 
{
  if( self->size == 0 ){
    free(self->data);
    self->capacity = 0;
  }
  if( self->size == 1 ){
    self->data[0] = 0;
    self->capacity = 0;
    self->size = 0;
  }else{
    assert(!array_empty(self));
    self->data[array_size(self)] = 0;
    self->size--;
    self->capacity--;
  } 
}
/*
 * Insert an element in the array (preserving the order)
 * @param struct array *self
 * @param int data
 * @param size_t index
 */
void array_insert(struct array *self, int data, size_t index) 
{
//
  if(self->capacity <= array_size(self)+1)  array_grow(self);
    //--insert end.
    if( index == array_size(self) )
    {
      self->data[index] = data;
      self->size=self->size+1;
    }else{
      //--insert first.
      if(index==0)
      {
        for(size_t i = array_size(self)+1; i > 0 ;i--)  self->data[i]=self->data[i-1];
      self->data[0] = data;
      self->size = self->size+1;
      }
      else
      {
        //--insert midddle.
        for(size_t i = array_size(self)+1; i > index ;i--)  self->data[i]=self->data[i-1];
      self->data[index]=data;
      self->size=self->size+1;
      }
  }
}
/*
 * sync size and capacity to - x
 * @param struct array *self
 * @param size_t x
 */
void array_sycro_less_one(struct array *self, size_t x) 
{
  self->capacity = self->capacity-x;
  self->size = self->size-x;
}

/*
 * Remove an element in the array (preserving the order)
 */
void array_remove(struct array *self, size_t index) 
{
  //--remove end.
  if (index == array_size(self) ) array_sycro_less_one(self,1);
  else
  {
    //--remove first.
    if(index == 0)
    {
      for(size_t i = 0; i < array_size(self) ;i++)  self->data[i] = self->data[i+1];
      array_sycro_less_one(self,1);
    }
    else
    {
      //--remove midddle.
      for(size_t i = index; i < array_size(self) ;i++)  self->data[i]=self->data[i+1];
      array_sycro_less_one(self,1);
    }
  }

}
/*
 * Get an element at the specified index in the array, or 0 if the index is not valid
 * @param struct array *self
 * @param size_t index
 */
int array_get(const struct array *self, size_t index) 
{
  if( index > array_size(self) || index == array_size(self))
  {
    return self->data[index];
  }
  else
  {
    return self->data[index];
  }
}
/*
 * Set an element at the specified index in the array to a new data, or do nothing if the index is not valid
 * @param struct array *self
 * @param size_t index
 * @param int data
 */
void array_set(struct array *self, size_t index, int data) 
{
  if( (index > array_size(self) || index == array_size(self)) )
  {
    return;
  }
  else
  {
    self->data[index]=data; 
  }
}
/*
 * Search for an element in the array.
 * @param struct array *self
 * @param int data
 */
size_t array_search(const struct array *self, int data) 
{
  if(!array_empty(self))
	{
		size_t res = 0;
		for(size_t i = 0; i < self->size; i++)	
		{
			if(self->data[i] == data) return res;
			res++;
		}
		return res;
	}
return 0;
}

/*
 * Search for an element in the sorted array.
 * @param struct array *self
 * @param int data
 */
size_t array_search_sorted(const struct array *self, int data) 
{
size_t res = self->size;
	for (size_t i = 0; i < self->size; i++)
  {
		if (self->data[i] == data)  res = i;
	}
return res;
}
/*
 * Tell if the array is sorted
 * @param const struct array *self
 */
bool array_is_sorted(const struct array *self) 
{
  for(size_t i = 1; i < self->size ; i++)
	{
		if(self->data[i-1] > self->data[i]) return false;
	}
return true;
}

/*
 * swap betwin indice i and j in the array
 * @param struct array *self
 * @param size_t i
 * @param size_t j
 */
void array_swap(struct array *self, size_t i, size_t j)
{
  size_t swap = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = swap;
}
/*
 * Make a partition of the array between i and j (inclusive) and returns the index of the pivot
 * @param struct array *self
 * @param ptrdiff_t i
 * @param ptrdiff_t j
 */
ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) 
{
  ptrdiff_t  pivot_index = i;
  ptrdiff_t  pivot = self->data[pivot_index];
  ptrdiff_t  l = i;
  array_swap(self, pivot_index, j);
  for (ptrdiff_t  k = i; k < j; ++k) 
  {    
    if (self->data[k] < pivot ) 
    {
      array_swap(self, k, l);
      l++;
    }
  }
  array_swap(self, l, j);
  return l;
}

/*
 * Make a sort partition of the array between i and j (recurcive) 
 * @param struct array *self
 * @param ptrdiff_t i
 * @param ptrdiff_t j
 */
void array_sort_partial(struct array *self, ptrdiff_t i, ptrdiff_t j)
{
  if (i < j)
  {
    ptrdiff_t p = array_partition(self, i, j);
    array_sort_partial(self, i, p - 1);
    array_sort_partial(self, p + 1, j);
  }
}
/*
 * Sort the array with quick sort
 * @param struct array *self
 */
void array_quick_sort(struct array *self) 
{
  array_sort_partial(self, 0, self->size - 1);
}

/*
 * Insert a data in a heap
 * @param struct array *self
 * @param size_t n
 * @param int data
 */
void array_heap_insert(struct array *self, size_t n, int data) 
{
  size_t i = n;
  self->data[i] = data;
  while (i > 0) 
  {
    size_t j = (i - 1) / 2;
    if (self->data[i] < self->data[j]) break;
    array_swap(self, i, j);
    i = j;
  }
}

/*
 * Remove a data from a heap
 * @param struct array *self
 * @param size_t n
 */
void array_heap_remove(struct array *self, size_t n) 
{
  self->data[0] = self->data[n - 1];
  size_t i = 0;
  while (i < (n - 1) / 2) 
  {
    size_t lt = 2 * i + 1;
    size_t rt = 2 * i + 2;
    if (self->data[i] > self->data[lt] && self->data[i] > self->data[rt]) break;
    // x?y:z; if(x) y else z
    size_t j = (self->data[lt] > self->data[rt]) ? lt : rt;
    array_swap(self, i, j);
    i = j;
  }
}
/*
 * Sort the array with heap sort
 * @param struct array *self
 */
void array_heap_sort(struct array *self) 
{
  for (size_t i = 0; i < self->size; ++i) 
  {
    size_t data = self->data[i];
    array_heap_insert(self, i, data);
  }
  for (size_t i = 0; i < self->size; ++i) 
  {
    size_t data = self->data[0];
    array_heap_remove(self, self->size - i);
    self->data[self->size - i - 1] = data;
  }
}
/*
 * Tell if the array is heap
 * @param const struct array *self
 */
bool array_is_heap(const struct array *self) 
{
  if (!self->data) return true;
  for (size_t i = 0; i < self->size; ++i) 
  {
    if (self->size >= 2*i+2) 
    {
      if (self->data[i] < self->data[2*i+1]) return false;
      if (self->size >= 2*i+3) 
      {
        if (self->data[i] < self->data[2*i+2]) return false; 
      }
    }
  }
return true;
}
/*
 * add a data in a heap
 * @param struct array *self
 * @param int data
 */
void array_heap_add(struct array *self, int data) 
{
  size_t i = self->size;
  array_push_back(self, data);
  while (i > 0) 
  {
    size_t j = (i-1)/2;
    if (self->data[i] < self->data[j]) break;
    array_swap(self, i, j);
    i = j;
  }
}
/*
 * return top of heap
 * @param const struct array *self
 */
int array_heap_top(const struct array *self) 
{
  return  self->data[0];
}
/*
 * remove top of heap
 * @param struct array *self
 */
void array_heap_remove_top(struct array *self) 
{
  array_heap_remove(self, self->size);  
  self->size--;
}

/*
 * list
 */

/*
 * Create an empty list
 * @param struct list *self
 */
void list_create(struct list *self) 
{
  self->first = NULL;
}
/*
 * Create a list with initial content recurcive without init call
 * @param struct list *self
 * @param const int *other
 * @param size_t size
 */
void list_create_from_rec(struct list *self, const int *other, size_t size) 
{
  // Last Call
  if( size == 0 ) return;
  struct list_node *node = malloc(sizeof(struct list_node)); 
  node->data = other[size-1];
  node->next = self->first;
  self->first = node;
  // Rec call
  list_create_from_rec(self, other, size-1); 
}
/*
 * Create a list with initial content
 * @param struct list *self
 * @param const int *other
 * @param size_t size
 */
void list_create_from(struct list *self, const int *other, size_t size) 
{
  // Init call
  list_create(self);
  //Rec call
  list_create_from_rec(self, other, size); 
}

/*
 * Destroy a list
 * @param struct list *self
 */
void list_destroy(struct list *self)
{
  if(!list_empty(self))
	{
		struct list_node *curr_node = self->first;
		struct list_node *next;
		while(curr_node != NULL)
		{
			next = curr_node->next;
			free(curr_node);
			curr_node = next;
		}
	}
}
/*
 * Tell if the list is empty
 * @param struct list *self
 * @return bool
 */
bool list_empty(const struct list *self) 
{
  return (!self->first) ? true : false ;
}

/*
 * Get the size of the list_node recurcive
 * @param const struct list_node *node
 * @return size_t
 */
size_t list_size_rec(const struct list_node *node)
{
  if( !node->next ) return 1; 
  return 1 + list_size_rec(node->next);
}

/*
 * Get the size of the list
 * @param const struct list *self
 * @return size_t
 */
size_t list_size(const struct list *self) 
{
  if( !self  || !self->first )  return 0;
  return list_size_rec( self->first );
}

/*
 * Compare the list to an array (data and size)
 * @param const struct list *self
 * @param const int *data
 * @param size_t size
 * @return bool
 */
bool list_equals(const struct list *self, const int *data, size_t size) 
{
  if( list_size(self) == size )
  {
    struct list_node *curr_node = self->first;
    size_t i = 0;
      while( curr_node )
      {
        if( curr_node->data != data[i] )  return false;
        curr_node = curr_node->next;
        i++;
      }
  return true;
  }
return false;
}

/*
 * Add an element in the list at the beginning
 * @param struct list *self
 * @param int data
 */
void list_push_front(struct list *self, int data) 
{
  struct list_node *curr_node = malloc(sizeof(struct list_node));
  curr_node->data = data;
  curr_node->next = self->first;
  self->first = curr_node;
}

/*
 * Remove the element at the beginning of the list
 * @param struct list *self
 */
void list_pop_front(struct list *self) 
{
  struct list_node *curr_node = self->first->next;
  free( self->first );
  self->first = curr_node;
}

/*
 * Add an element in the list at the end
 * @param struct list *self
 * @param int data
 */
void list_push_back(struct list *self, int data) 
{
  struct list_node *node = malloc(sizeof(struct list_node));
  node->next = NULL;
  node->data = data;
    if(list_empty(self))
    {
      self->first = node;
      return;
    }
    struct list_node *curr_node = self->first;
    while( curr_node->next  )  curr_node = curr_node->next;
    curr_node->next = node;
}

/*
 * Remove the element at the end of the list
 * @param struct list *self
 */
void list_pop_back(struct list *self) 
{
  if( list_size(self) == 0 )  return;
  if( list_size(self) == 1 )
  {
    free(self->first);
    self->first = NULL;
    return;
  }
  struct list_node *curr_node = self->first;
  while ( curr_node->next->next ) curr_node = curr_node->next;
  free(curr_node->next);
  curr_node->next = NULL;
}

/*
 * Insert an element in the list (preserving the order)
 * index is valid or equals to the size of the list (insert at the end)
 * @param struct list *self
 * @param int data
 * @param size_t index
 */
void list_insert(struct list *self, int data, size_t index) 
{
  if( index >= list_size( self ) )
  {
    list_push_back( self,data );
  }
  else
  {
  struct list_node *first_node = malloc(sizeof(struct list_node));
  first_node->data = data;
    if( index == 0 )
    {
      list_push_front( self,data );
    }
    else
    {
    struct list_node *second_node = self->first;
      for(size_t i = 1; i < index ; i++)  second_node = second_node->next;
    // creat third_node to swape betwin first and second node
    struct list_node *third_node = malloc(sizeof(struct list_node));
      third_node = second_node->next;
      second_node->next = first_node;
      first_node->next = third_node;
    }
  }
}
/*
 * Remove an element in the list (preserving the order)
 * index is valid
 * @param struct list *self
 * @param size_t index
 */
void list_remove(struct list *self, size_t index) 
{
if( index >= list_size(self) )
{
  struct list_node *first_node = self->first;
  while( first_node->next->next ) first_node = first_node->next;
  free( first_node->next );
  first_node->next = NULL;
  }
  else
  {
    if(index == 0)
    {
      struct list_node *second_node = self->first->next;
      free( self->first );
      self->first = second_node;
    }
    else
    {
    struct list_node *third_node = self->first;
      for(size_t i = 1; i < index ; i++)  third_node = third_node->next;
    struct list_node *fourth_node = third_node->next->next;
    free( third_node->next );
    third_node->next = fourth_node;
    }
  }
}

/*
 * Get the element at the specified index in the list or 0 if the index is not valid
 * @param struct list *self
 * @param size_t index
 */
int list_get(const struct list *self, size_t index) 
{
  const size_t LENGTH_LIST = list_size(self)-1;
    if( list_empty(self) || LENGTH_LIST < index ) return 0;
  struct list_node *curr_node = self->first;
    for(size_t i = 0; i < index; i++) curr_node = curr_node->next;
return curr_node->data;
}
  
/*
 * Set an element at the specified index in the list to a new data, or do nothing if the index is not valid
 * @param struct list *self
 * @param size_t index
 * @param int data
 */
void list_set(struct list *self, size_t index, int data) 
{
  const size_t LENGTH_LIST = list_size(self)-1;
    if( list_empty( self ) || LENGTH_LIST < index ) return;
  struct list_node *curr_node = self->first;
    for(size_t i = 0; i < index; i++) curr_node = curr_node->next;
  curr_node->data = data;
}

/*
 * Search for an element in the list and return its index or the size of the list if not present.
 * @param struct list *self
 * @param  int data
 * @return size_t res
 */
size_t list_search(const struct list *self, int data) 
{
  if( list_empty(self) )  return list_size(self);
  size_t res = 0;
  struct list_node *curr_node = self->first;
    while( curr_node->data != data && curr_node->next != NULL )
    {
      curr_node = curr_node->next;
      res++;
    }
    res = ( curr_node->data == data ) ? res : list_size(self) ;
return res; 
}

/*
 * Tell if a list is sorted
 * @param const struct list *self
 * @return bool
 */
bool list_is_sorted(const struct list *self) 
{
if( list_size(self) >= 2 )
{
  struct list_node *curr_node = self->first;
  while( curr_node->next )
  {
    if( curr_node->data > curr_node->next->data ) return false;
    curr_node = curr_node->next;
  }
}
return true;
}
/*
 * Split a list in two. At the end, self should be empty.
 * @param struct list *self
 * @param struct list *out1
 * @param struct list *out2
 */
void list_split(struct list *self, struct list *out1, struct list *out2) 
{
  struct list_node *curr_node = self->first ;
  for(size_t i = 0; i < list_size(self); i++)
  {
  ( i % 2 ) ? list_push_back( out1,curr_node->data ) : list_push_back( out2,curr_node->data );
  curr_node = curr_node->next;
  }
  list_destroy( self );
  self->first = NULL;
}
/*
 *list_push_back and pop_front
 * @param struct list *self
 * @param struct list *in1
 */
void list_push_back_pop_front(struct list *self, struct list *in) 
{
  list_push_back(self,in->first->data);
  if ( !self ) return false;
  if ( data < self->data ) tree_remove_node(self->left, data);
  if ( data > self->data ) tree_remove_node(self->right, data);
void list_merge(struct list *self, struct list *in1, struct list *in2) 
{
while( in1->first && in2->first ) ( in1->first->data < in2->first->data ) ? list_push_back_pop_front(self,in1) : list_push_back_pop_front(self,in2) ;
while( in1->first ) list_push_back_pop_front( self , in1 );
while( in2->first ) list_push_back_pop_front( self , in2 ); 
}
/*
 * Sort a list with merge sort
 * @param struct list *self
 */
void list_merge_sort(struct list *self) 
{
  struct list *in1 = malloc(sizeof(struct list));
  list_create( in1 );
  struct list *in2 = malloc(sizeof(struct list));
  list_create( in2 );
  while( !list_is_sorted( self ) )list_split( self , in1 , in2 ), list_merge( self , in1 , in2 );
  free( in1 );
  free( in2 );
}

/*
 * tree
 */
 
/*
 * Create an empty tree
 * @param struct tree *self
 */
void tree_create(struct tree *self) 
{
  self->root = NULL;
}

/*
 * Destroy a tree_node
 * @param struct tree *self
 */
void tree_node_destroy(struct tree_node *self) 
{
  if ( self->left ) tree_node_destroy( self->left );
  if ( self->right ) tree_node_destroy( self->right ); 
  free( self ); 
}

/*
 * Destroy a tree
 * @param struct tree *self
 */
void tree_destroy(struct tree *self)
{
  if ( self->root ) tree_node_destroy( self->root );
}

/*
 * Tell if the tree is empty
 * @param const struct tree *self
 * @return bool
 */
bool tree_empty(const struct tree *self) 
{
  if ( !self->root ) return true;
return false;
}

/*
 * Get the size of the tree_node rec
 * @param const struct tree_node *self
 * @return size_t
 */
size_t tree_node_size_rec(const struct tree_node *self) 
{
  if ( !self ) return 0; 
  if ( !self->right && !self->left ) return 1;
return 1 + tree_node_size_rec( self->left ) + tree_node_size_rec( self->right );
}

/*
 * Get the size of the tree
 * @param const struct tree *self
 * @return size_t
 */
size_t tree_size(const struct tree *self) 
{
  return tree_node_size_rec( self->root );
}

/*
 * Get the height of the tree_node rec in left and right side of tree
 * @param struct tree_node *self
 * @return size_t
 */
size_t tree_node_height(struct tree_node *self){ 
	size_t height_left, height_right;
	if (!self)  return 0;
	height_left = tree_node_height( self->left );
	height_right = tree_node_height( self->right );
return 1 + ( (height_left > height_right) ? height_left : height_right );
}

/*
 * Get the height of the tree
 * @param const struct tree *self
 * @return size_t
 */
size_t tree_height(const struct tree *self) 
{
  return tree_node_height( self->root );
}

/*
 * Tell if a data is in the tree_node
 * @param struct tree_node *self
 * @param int data
 * @return bool
 */
bool tree_node_contains(const struct tree_node *self, int data) 
{
  if ( !self ) return false;
  if (data > self->data) return tree_node_contains( self->right, data );
  if (data < self->data) return tree_node_contains( self->left, data );
return true;
}

/*
 * Tell if a data is in the tree
 * @param const struct tree *self
 * @param int data
 * @return bool
 */
bool tree_contains(const struct tree *self, int data)
{
  return tree_node_contains(self->root, data);
}
/*
 * Insert a data in the tree_node recurcive
 * @param struct tree *self
 * @param int data
 * @return struct tree_node self
 */
struct tree_node *tree_node_insert(struct tree_node *self, int data) 
{
  if ( !self ) 
  {
    struct tree_node *temp = malloc(sizeof(struct tree_node));
    temp->left = temp->right = NULL;
    temp->data = data;
    self = temp;
  }
  if (data < self->data) self->left = tree_node_insert(self->left, data);
  if (data > self->data) self->right = tree_node_insert(self->right, data);
return self;
}
/*
 * Insert a data in the tree and return false if the data was already present
 * @param struct tree *self
 * @param int data
 * @return bool insert 
 */
bool tree_insert(struct tree *self, int data) 
{
  bool insert = false;
   if ( !self->root ) 
   {
    struct tree_node *t = malloc(sizeof(struct tree_node));
    t->left = t->right = NULL;
    t->data = data;
    self->root = t;
    insert = true;
  }
  else 
  {
    if(tree_contains(self,data)){
    insert = false;
    }else{
    self->root = tree_node_insert(self->root, data);
    insert = true;
    }
  }
return insert ;
}
/*
 * Remove a data from the tree_node and return false if the data was not present
 * @param struct tree_node *self
 * @param int data
 * @return bool 
 */
bool tree_remove_node(struct tree_node *self, int data) 
{
  if ( !self ) return false;
  if ( data < self->data ) tree_remove_node(self->left, data);
  if ( data > self->data ) tree_remove_node(self->right, data);
  if ( data == self->data ){
  //tree_node_destroy(self->left);
  return true;
  }
}

/*
 * Remove a data from the tree and return false if the data was not present
 * @param struct tree *self
 * @param int data 
 * @return bool
 */
bool tree_remove(struct tree *self, int data) 
{
 return tree_remove_node( self->root, data );
}

/*
 * A function type that takes an int and a pointer and returns void
 */
//typedef void (*tree_func_t)(int data, void *user_data);

/*
 * Walk in the tree_node in pre order and call the function with user_data as a second argument
 * @param struct tree_node *self
 * @param tree_func_t func
 * @param void *user_data
 */
void tree_node_walk_pre_order_part(struct tree_node *self, tree_func_t func, void *user_data){
  if ( tree_node_size_rec(self) == 0 )  return;
  //pre_order
  func(self->data,user_data);
  if( self->right )tree_node_walk_pre_order_part(self->right,func,user_data);
  if( self->left )tree_node_walk_pre_order_part(self->left,func,user_data);
}

/*
 * Walk in the tree_node in in order and call the function with user_data as a second argument
 * @param struct tree_node *self
 * @param tree_func_t func 
 * @param void *user_data
 */
void tree_node_walk_in_order_part(struct tree_node *self, tree_func_t func, void *user_data){
  if ( tree_node_size_rec(self) == 0 )  return;
  if( self->left ) tree_node_walk_in_order_part( self->left,func,user_data );
  //in_order
  func(self->data,user_data);
  if( self->right )tree_node_walk_in_order_part( self->right,func,user_data );
}

/*
 * Walk in the tree_node in post order and call the function with user_data as a second argument
 * @param struct tree_node *self
 * @param tree_func_t func 
 * @param void *user_data
 */
void tree_node_walk_post_order_part(struct tree_node *self, tree_func_t func, void *user_data){
  if ( tree_node_size_rec(self) == 0 )  return;
  if( self->right )tree_node_walk_post_order_part( self->right,func,user_data );
  if( self->left )tree_node_walk_post_order_part( self->left,func,user_data );
  //post_order
  func(self->data,user_data);
}

/*
 * Walk in the tree in pre order and call the function with user_data as a second argument
 * @param const struct tree *self  
 * @param tree_func_t func
 * @param void *user_data
 */
void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  
{
  tree_node_walk_pre_order_part( self->root,func,user_data );
}

/*
 * Walk in the tree in in order and call the function with user_data as a second argument
 * @param const struct tree *self
 * @param tree_func_t func
 * @param void *user_data
 */
void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) 
{
  tree_node_walk_in_order_part( self->root,func,user_data );  
}

/*
 * Walk in the tree in post order and call the function with user_data as a second argument
 * @param const struct tree *self
 * @param tree_func_t func
 * @param void *user_data
 */
void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data)
{
  tree_node_walk_post_order_part( self->root,func,user_data );
}

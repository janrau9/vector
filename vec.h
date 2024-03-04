#ifndef VEC_H
#define VEC_H

#include <stdlib.h>

/*
    vec struct is a thick pointer
    vec struct is a dynamic array
    users of vec should not access theses members directly
    instead use the operations exposed in the functions below.
*/

typedef struct s_vec {
    size_t item_size; // size of each item in bytes
    size_t length; // number of items currently in the vec
    size_t capacity; // number of items that can be stored in the vec
    void *buffer; // heap memory to store the items
} t_vec;

/*
constructor
constructs a new vec with the given item size
vec_drop when lifetime expires

params:
    item_size: size of each item in bytes
    capacity: number of items that can be stored in the vec
returns:  
    initialized vec value
*/

t_vec vec_value(size_t capacity, size_t item_size);

/*
owner must call to expire a vec value's lifetime.
frees the memory allocated for the vec's buffer.
resets length, capacity to zero, buffer to NULL.
*/

void    vec_drop(t_vec *self);

/*accessor*/

/*returns the number of items in the vec*/
size_t  vec_length(const t_vec *self);

/*returns a pointer to the items array for reading only
you should not write to the returned memory directly*/

void *vec_items(const t_vec *self);

/*operations*/

/*get a pointer to the item at index.
you may write to this reference but not beyond it
*/

void    *vec_ref(const t_vec *self, size_t index);

/*copy the item at index to the memory of out*/

void    vec_get(const t_vec *self, size_t index, void *out);

/*
assign an item at index to be a copy of value
valid indices include 0 to length.
when the index is equal to length, the item is appended to the vec
*/

void vec_set(t_vec *self, size_t index, const void *value);





#endif
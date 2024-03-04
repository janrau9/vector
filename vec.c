#include <string.h>
#include <stdio.h>
#include "vec.h"

t_vec vec_value(size_t capacity, size_t item_size)
{
    t_vec vec;

    vec.capacity = capacity;
    vec.item_size = item_size;
    vec.length = 0;
    vec.buffer = calloc(capacity, item_size);
    if (vec.buffer == NULL)
    {
        fprintf(stderr, "vec_value: malloc failed\n");
        exit(1);
    }
    return vec;
}

void vec_drop(t_vec *self)
{
    free(self->buffer);
    self->buffer = NULL;
    self->capacity = 0;
    self->length = 0;
}

size_t vec_length(const t_vec *self)
{
    return self->length;
}

void *vec_items(const t_vec *self)
{
    return self->buffer;
}

void *vec_ref(const t_vec *self, size_t index)
{
    if (index >= self->length)
    {
        fprintf(stderr, "vec_ref: index out of range\n");
        exit(1);
    }
    return (char *)self->buffer + (index * self->item_size);
}

void vec_set(t_vec *self, size_t index, const void *value)
{
    ensure_capacity(self, index + 1);
    memcpy(vec_ref(self, index), value, self->item_size);
    if (index >= self->length)
    {
        self->length = index + 1;
    }
}

void    vec_get(const t_vec *self, size_t index, void *out)
{
    if (index >= self->length)
    {
        fprintf(stderr, "vec_get: index out of range\n");
        exit(1);
    }
    memcpy(out, vec_ref(self, index), self->item_size);
}

static void ensure_capacity(t_vec *self, size_t n)
{
    if (n > self->capacity)
    {
        size_t new_capacity = self->capacity * 2;
        self->buffer = realloc(self->buffer, new_capacity * self->item_size);
        if (self->buffer == NULL)
        {
            fprintf(stderr, "ensure_capacity: realloc failed\n");
            exit(1);
        }
        self->capacity = new_capacity;
    }
}
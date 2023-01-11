#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "registro.h"
#include "pagina.h"

typedef entry_number_t buffer_size_t;

typedef struct buffer_t{
    buffer_size_t bsize;
    page_t* bentry[bsize];
} buffer_t;

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr);
int ADD_PAGE_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, page_t* page);
int DELETE_PAGE_FROM_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index);
int DELETE_BUFFER(buffer_t* buffer_ptr);

#endif
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "registro.h"
#include "pagina.h"

typedef entry_number_t buffer_size_t;

typedef char buffer_slot_usage_t;
enum SLOT_USAGE{NOT_IN_USE, IN_USE};

typedef struct buffer_slot_t{
    buffer_slot_usage_t busage;
    page_t bentry;
} buffer_slot_t;

typedef struct buffer_t{
    buffer_size_t bsize;
    buffer_slot_t* bslots[bsize];
} buffer_t;

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr);
int FIND_FIRST_UNUSED_SLOT(buffer_t* buffer_ptr, buffer_slot_t* first_slot_ptr, buffer_size_t* first_slot_index);
int ADD_PAGE_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, page_type_t page_type, FILE* fp, long int offset);
int ADD_BLOCK_TO_BUFFER(buffer_t* buffer_ptr, page_type_t page_type, FILE* fp, page_value_t first_page_of_block, page_value_t last_page_of_block);
int ADD_FILE_TO_BUFFER(buffer_t* buffer_ptr, page_type_t page_type, FILE* fp);
int DELETE_PAGE_FROM_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index);
int DELETE_BUFFER(buffer_t* buffer_ptr);

#endif
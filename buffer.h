#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "pagina.h"

typedef entry_number_t buffer_size_t;

typedef union buffer_entry_type_t{
    pagina_aluno_t aluno;
    pagina_curso_t curso;
} buffer_entry_type_t;

typedef struct buffer_entry_t{
    union buffer_entry_t betype;
    pagina_type_t btype;
} buffer_entry_t;

typedef struct buffer_t{
    buffer_size_t bsize;
    buffer_entry_t* bentry[bsize];
} buffer_t;

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr);
int ADD_PAG_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, buffer_entry_type_t* pag, pagina_type_t pag_type);
int DELETE_PAG_FROM_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index);
int DELETE_BUFFER(buffer_t* buffer_ptr);

#endif
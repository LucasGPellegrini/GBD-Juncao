#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include <stdio.h>
#include "size.h"
#include "registro.h"

typedef memory_size_t page_size_t;
const page_size_t PAGE_SIZE = 4*K;

typedef struct page_entry_t{
    aluno_t* alunos;
    curso_t* cursos;
} page_entry_t;

typedef entry_type_t page_type_t;
typedef unsigned int page_value_t;

typedef struct page_t{
    page_entry_t pvalues;
    page_type_t ptype;
    page_value_t psize;
} page_t;

typedef char page_usage_t;

enum PAGE_TYPE{EMPTY_PAGE = 'e', ALUNO_PAGE = 'a', CURSO_PAGE = 'c'};

int VALID_PAGE_TYPE(page_type_t page_type);
int CREATE_PAGE(page_t* page, page_type_t page_type);
int PAGE_ENTRY_NUMBER(page_type_t page_type, page_value_t* page_entry_number);
int COPY_TO_PAGE(page_t* page_to_copy_to, page_type_t page_type, FILE* fp, long int offset);
int EMPTY_THE_PAGE(page_t* page_to_empty);
int IS_EMPTY_PAGE(page_t* page);
int PRINT_PAGE(page_t* page);
int SAME_KEY(page_entry_t* rpage, page_value_t rvalue, entry_type_t rtype, size_t roffset, page_entry_t* spage, page_value_t svalue, entry_type_t stype, size_t soffset, size_t keysize);

#endif

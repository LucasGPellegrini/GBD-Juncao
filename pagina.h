#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include "registro.h"

typedef memory_size_t page_size_t;

const page_size_t PAGE_SIZE = 4*K;

typedef union page_entry_t{
    page_aluno_t* alunos;
    page_curso_t* cursos;
} page_entry_t;

typedef struct page_t{
    page_entry_t pvalues;
    page_type_t ptype;
    page_size_t psize;
} page_t;

typedef entry_type_t page_type_t;
typedef char page_usage_t;
typedef unsigned int page_value_t;

enum PAGE_TYPE{EMPTY = 'e', ALUNO = 'a', CURSO = 'c'};

int VALID_PAGE_TYPE(page_type_t page_type);
int CREATE_PAGE(page_t* page, page_type_t page_type);
int PAGE_SIZE(page_type_t page_type, size_t* page_size);
int COPY_TO_PAGE(page_t* page_to_copy_to, page_type_t page_type, FILE* fp, long int offset);
int EMPTY_PAGE(page_t* page_to_empty);
int IS_EMPTY_PAGE(page_t* page);
int PRINT_PAGE(page_t* page);

#endif

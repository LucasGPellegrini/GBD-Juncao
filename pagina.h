#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include "registro.h"
#include "size.h"

#define PAG_SIZE 4*K

typedef struct aluno{
    aluno[PAG_SIZE / sizeof(struct aluno)]
} pagina_aluno_t;

typedef struct curso{
    curso[PAG_SIZE / sizeof(struct curso)]
} pagina_curso_t;

typedef char pagina_type_t;

enum PAG_TYPE{VAZIO = 'v', ALUNO = 'a', CURSO = 'c'};

int VALID_PAG_TYPE(pagina_type_t pag_type);

#endif

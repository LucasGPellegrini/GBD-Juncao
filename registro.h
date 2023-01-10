#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#pragma pack(1)

#define CODIGO_CURSO_SIZE 3
#define NOME_ALUNO_SIZE 33
#define CODIGO_CURSO_SIZE 3
#define NOME_CURSO_SIZE 17

#include <limits.h>
#define ENTRY_MAX INT_MAX

typedef unsigned int entry_number_t;

struct aluno{
	entry_number_t seq_aluno;
	char codigo_curso[CODIGO_CURSO_SIZE];
	char nome_aluno[NOME_ALUNO_SIZE];
};

typedef struct aluno* aluno_t;

struct curso{
	entry_number_t seq_curso;
	char codigo_curso[CODIGO_CURSO_SIZE];
	char nome_curso[NOME_CURSO_SIZE];
};

typedef struct curso* curso_t;

#endif
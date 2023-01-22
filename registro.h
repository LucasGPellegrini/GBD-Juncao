#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#pragma pack(1)

#define CODIGO_CURSO_SIZE 3
#define NOME_ALUNO_SIZE 33
#define CODIGO_CURSO_SIZE 3
#define NOME_CURSO_SIZE 17

#include <limits.h>
#define ENTRY_MAX UINT_MAX

typedef unsigned int entry_number_t;

typedef struct aluno{
	entry_number_t seq_aluno;
	char codigo_curso[CODIGO_CURSO_SIZE];
	char nome_aluno[NOME_ALUNO_SIZE];
} aluno_t;

typedef struct curso{
	entry_number_t seq_curso;
	char codigo_curso[CODIGO_CURSO_SIZE];
	char nome_curso[NOME_CURSO_SIZE];
} curso_t;

typedef char entry_type_t;
enum ENTRY_TYPE{ALUNO_ENTRY = 'a', CURSO_ENTRY = 'c'};

int VALID_ENTRY_TYPE(entry_type_t entry_type);
int PRINT_ENTRY(void* entry, entry_type_t entry_type);

#endif
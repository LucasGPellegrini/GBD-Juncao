#include "registro.h"
#include <stddef.h>
#include <stdio.h>

int VALID_ENTRY_TYPE(entry_type_t entry_type){
    return entry_type == ALUNO_ENTRY || entry_type == CURSO_ENTRY;
}

int PRINT_ENTRY(void* entry, entry_type_t entry_type){
    if(entry == NULL || !VALID_ENTRY_TYPE(entry_type)) return 0;

    switch(entry_type){
        case ALUNO_ENTRY:
            aluno_t* aluno = (aluno_t*) entry;
            printf("Seq Aluno = %u\n", aluno->seq_aluno);
            printf("Nome Aluno = %s\n", aluno->nome_aluno);
            printf("Codigo Curso do Aluno = %s", aluno->codigo_curso);
            break;

        case CURSO_ENTRY:
            curso_t* curso = (curso_t*) entry;
            printf("Seq Curso = %u\n", curso->seq_curso);
            printf("Nome Curso = %s\n", curso->nome_curso);
            printf("Codigo Curso = %s", curso->codigo_curso);
            break;
    }

    return 1;
}
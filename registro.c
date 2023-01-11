#include "registro.h"


int VALID_ENTRY_TYPE(entry_type_t entry_type){
    return entry_type == 'a' || entry_type == 'c';
}

int PRINT_ENTRY(void* entry, entry_type_t entry_type){
    if(entry == NULL || !VALID_ENTRY_TYPE(entry_type)) return 0;

    switch(entry_type){
        case ALUNO:
            struct aluno* aluno = (struct aluno*) entry;
            printf("Seq Aluno = %u\n", aluno->seq_aluno);
            printf("Nome Aluno = %s\n", aluno->nome_aluno);
            printf("Codigo Curso do Aluno = %s", aluno->codigo_curso);
            break;

        case CURSO:
            struct curso* curso = (struct curso*) entry;
            printf("Seq Curso = %u\n", aluno->seq_curso);
            printf("Nome Curso = %s\n", aluno->nome_curso);
            printf("Codigo Curso = %s", aluno->codigo_curso);
            break;
    }

    return 1;
}
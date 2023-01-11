#include "pagina.h"

int VALID_PAGE_TYPE(page_type_t page_type){
    return page_type == 'e' || page_type == 'a' || page_type == 'c';
}

int CREATE_PAGE(page_t* page, page_type_t page_type){
    if(page == NULL || !VALID_PAGE_TYPE(page_type) || page_type == EMPTY) return 0;

    page = malloc(sizeof(page_t));
    if(page == NULL) return 0;

    switch(page_type){
        case ALUNO:
            page->ptype = ALUNO;
            page->psize = PAG_SIZE / sizeof(struct aluno);
            page->pvalues->alunos = malloc(page->psize * sizeof(struct aluno));
            if(page->pvalues->alunos == NULL){
                free(page);
                return 0;
            }
            break;

        case CURSO:
            page->ptype = CURSO;
            page->psize = PAG_SIZE / sizeof(struct curso);
            page->pvalues->cursos = malloc(page->psize * sizeof(struct cursos));
            if(page->pvalues->cursos == NULL){
                free(page);
                return 0;
            }
            break;
    }

    return 1;
}

int COPY_TO_PAGE(page_t* page_to_copy_to, page_type_t page_type, FILE* fp, long int offset){
    if(page_to_copy_to == NULL || !VALID_PAGE_TYPE(page_type) || fp == NULL || offset < 0) return 0;

    switch(page_type){
        case ALUNO:
            fseek(fp, offset, SEEK_SET);
            if(fread(page_to_copy_to->pvalues->alunos, sizeof(struct aluno), page_to_copy_to->psize, fp) != page_to_copy_to->psize) return 0;
            page_to_copy_to->ptype = ALUNO;
            break;

        case CURSO:
            fseek(fp, offset, SEEK_SET);
            if(fread(page_to_copy_to->pvalues->cursos, sizeof(struct curso), page_to_copy_to->psize, fp) != page_to_copy_to->psize) return 0;
            page_to_copy_to->ptype = CURSO;
            break;
    }

    return 1;
}

int EMPTY_PAGE(page_t* page_to_empty){
    if(page_to_empty == NULL) return 0;

    page_to_empty->ptype = EMPTY;

    return 1;
}

int IS_EMPTY_PAGE(page_t* page){
    return page != NULL && page->ptype == EMPTY;
}

int PRINT_PAGE(page_t* page){
    if(page == NULL || !VALID_PAGE_TYPE(page->ptype)) return 0;

    if(page->ptype == EMPTY) printf("Empty page!");
    else{
        for(page_size_t i = 0; i < page->psize; i++){
            if(page->ptype == ALUNO)
                if(!PRINT_ENTRY(&page->pvalues->alunos[i], page->ptype)) return 0;
            else
                if(!PRINT_ENTRY(&page->pvalues->cursos[i], page->ptype)) return 0;

            printf("\n\n---------------------\n\n");
        }
    }
    
    return 1;
}
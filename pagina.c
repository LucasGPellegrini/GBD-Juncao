#include <stdlib.h>
#include <stdio.h>
#include "pagina.h"
#include "registro.h"

int VALID_PAGE_TYPE(page_type_t page_type){
    return page_type == EMPTY_PAGE || page_type == ALUNO_PAGE || page_type == CURSO_PAGE;
}

int CREATE_PAGE(page_t* page, page_type_t page_type){
    if(page == NULL || !VALID_PAGE_TYPE(page_type) || page_type == EMPTY_PAGE) return 0;

    page = malloc(sizeof(page_t));
    if(page == NULL) return 0;

    page_value_t page_entry_number;
    PAGE_ENTRY_NUMBER(page_type, &page_entry_number);
    // How many entries fit to page
    page->psize = page_entry_number;

    switch(page_type){
        case ALUNO_PAGE:
            page->ptype = ALUNO_PAGE;
            page->pvalues.alunos = malloc(page->psize * sizeof(aluno_t));
            if(page->pvalues.alunos == NULL){
                free(page);
                return 0;
            }
            page->pvalues.cursos = NULL;
            break;

        case CURSO_PAGE:
            page->ptype = CURSO_PAGE;
            page->pvalues.cursos = malloc(page->psize * sizeof(curso_t));
            if(page->pvalues.cursos == NULL){
                free(page);
                return 0;
            }
            page->pvalues.alunos = NULL;
            break;
    }

    return 1;
}

// How many entries fit to page given page type (i.e. the entry type)
int PAGE_ENTRY_NUMBER(page_type_t page_type, page_value_t* page_entry_number){
    if(!VALID_PAGE_TYPE(page_type) || page_entry_number == NULL) return 0;

    switch(page_type){
        case ALUNO_PAGE:
            *page_entry_number = PAGE_SIZE / sizeof(aluno_t);
            break;

        case CURSO_PAGE:
            *page_entry_number = PAGE_SIZE / sizeof(curso_t);
            break;
    }

    return 1;
}

int COPY_TO_PAGE(page_t* page_to_copy_to, page_type_t page_type, FILE* fp, long int offset){
    if(page_to_copy_to == NULL || !VALID_PAGE_TYPE(page_type) || fp == NULL || offset < 0) return 0;

    switch(page_type){
        case ALUNO_PAGE:
            fseek(fp, offset, SEEK_SET);
            if(fread(page_to_copy_to->pvalues.alunos, sizeof(aluno_t), page_to_copy_to->psize, fp) != page_to_copy_to->psize) return 0;
            page_to_copy_to->ptype = ALUNO_PAGE;
            break;

        case CURSO_PAGE:
            fseek(fp, offset, SEEK_SET);
            if(fread(page_to_copy_to->pvalues.cursos, sizeof(curso_t), page_to_copy_to->psize, fp) != page_to_copy_to->psize) return 0;
            page_to_copy_to->ptype = CURSO_PAGE;
            break;
    }

    return 1;
}

// Empty the page meaning set page type to empty
// Entries stored in page are going to be considered trash
int EMPTY_THE_PAGE(page_t* page_to_empty){
    if(page_to_empty == NULL) return 0;

    page_to_empty->ptype = EMPTY_PAGE;

    return 1;
}

int IS_EMPTY_PAGE(page_t* page){
    return page != NULL && page->ptype == EMPTY_PAGE;
}

int PRINT_PAGE(page_t* page){
    if(page == NULL || !VALID_PAGE_TYPE(page->ptype)) return 0;

    if(IS_EMPTY_PAGE(page)) printf("Empty page!");
    else{
        for(page_size_t i = 0; i < page->psize; i++){
            if(page->ptype == ALUNO_PAGE)
                if(!PRINT_ENTRY(&page->pvalues.alunos[i], page->ptype)) return 0;
            else
                if(!PRINT_ENTRY(&page->pvalues.cursos[i], page->ptype)) return 0;

            printf("\n\n---------------------\n\n");
        }
    }
    
    return 1;
}

int SAME_KEY(page_entry_t* rpage, page_value_t rvalue, entry_type_t rtype, size_t roffset, page_entry_t* spage, page_value_t svalue, entry_type_t stype, size_t soffset, size_t keysize){
    if(rpage == NULL || spage == NULL || !VALID_ENTRY_TYPE(rtype) || !VALID_ENTRY_TYPE(stype) || roffset < 0 || soffset < 0 || keysize <= 0 || rvalue < 0 || svalue < 0) return 0;

    char* rkey;
    char* skey;

    switch(rtype){
        case ALUNO_PAGE:
            rkey = (char*) &rpage->alunos[rvalue] + roffset;
            break;

        case CURSO_PAGE:
            rkey = (char*) &rpage->cursos[rvalue] + roffset;
            break;
    }

    
    switch(stype){
        case ALUNO_PAGE:
            skey = (char*) &spage->alunos[svalue] + soffset;
            break;

        case CURSO_PAGE:
            skey = (char*) &spage->cursos[svalue] + soffset;
            break;
    }

    size_t i;
    for(i = 0; i < keysize && rkey[i] == skey[i]; i++);

    return(i == keysize);
}
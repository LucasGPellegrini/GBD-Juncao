#include "arquivo.h"

int FILE_SIZE(FILE* fp, memory_size_t* fsize){
    if(fp == NULL || fsize == NULL) return 0;

    long int CURFP = ftell(fp);

    fseek(fp, 0, SEEK_END);
    *fsize = ftell(fp);
    
    fseek(fp, 0, CURFP);

    return 1;
}

int ENTRIES_PER_FILE(FILE* fp, entry_type_t etype, entry_number_t* eval){
    if(fp == NULL || !VALID_ENTRY_TYPE(etype) || eval == NULL) return 0;

    memory_size_t fsize;
    if(!FILE_SIZE(fp, &fsize)) return 0;

    switch(etype){
        case ALUNO_ENTRY:
            *eval = fsize / sizeof(aluno_t);
            break;
        case CURSO_ENTRY:
            *eval = fsize / sizeof(curso_t);
            break;
    }

    return 1;
}

int PAGES_PER_FILE(FILE* fp, page_type_t ptype, page_value_t* pval){
    if(fp == NULL || !VALID_PAGE_TYPE(ptype) || pval == NULL) return 0;

    entry_number_t eval;
    ENTRIES_PER_FILE(fp, ptype, &eval);

    *pval = eval % PAGE_SIZE == 0 ? eval / PAGE_SIZE :(eval / PAGE_SIZE) + 1;

    return 1;
}


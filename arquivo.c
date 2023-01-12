#include "arquivo.h"


int FILE_SIZE(FILE* fp, memory_size_t* fsize){
    if(fp == NULL || fsize == NULL) return 0;

    long int CURFP = ftell(fp);

    fseek(fp, 0, SEEK_END);
    *fsize = ftell(fp);
    
    fseek(fp, 0, CURFP);

    return 1;
}

int ENTRIES_PER_FILE(FILE* fp, entry_type_t etype, entry_value_t* eval){
    if(fp == NULL || !VALID_ENTRY_TYPE(etype) || eval == NULL) return 0;

    memory_size_t fsize;
    if(!FILE_SIZE(fp, &fsize)) return 0;

    switch(etype){
        case ALUNO:
            *eval = fsize / sizeof(struct aluno);
            break;
        case CURSO:
            *eval = fsize / sizeof(struct curso);
            break;
    }

    return 1;
}

int PAGES_PER_FILE(FILE* fp, entry_type_t etype, page_value_t* pval){
    if(fp == NULL || !VALID_PAGE_TYPE(ptype) || pval == NULL) return 0;

    entry_value_t eval;
    ENTRIES_PER_FILE(fp, etype, &eval);

    *pval = eval / PAGE_SIZE;

    return 1;
}


#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr){
    if(buffer_ptr == NULL || bsize <= 0) return 0;

    buffer_ptr = malloc(sizeof(buffer_t));
    if(buffer_ptr == NULL) return 0;

    buffer_ptr->bsize = bsize;

    page_t empty;
    empty.ptype = VAZIO;

    for(buffer_size_t i = 0; i < bsize; i++){
        buffer_ptr->bentry[i] = malloc(sizeof(buffer_entry_t));
        if(buffer_ptr->bentry[i] == NULL){
            for(buffer_size_t j = 0; j < i; j++){
                free(buffer_ptr->bentry[j]);
                free(buffer_ptr);
                return 0;
            }
        }

        EMPTY_PAGE(&buffer_ptr->bentry[i]);
    }

    return 1;
}

int ADD_PAGE_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, page_t* page){
    if(buffer_ptr == NULL || buffer_index < 0 || buffer_index >= buffer_ptr->bsize || page == NULL || !VALID_PAGE_TYPE(page->ptype) || page->ptype || !IS_EMPTY_PAGE(&buffer_ptr->bentry[buffer_index])) return 0;

    return COPY_TO_PAGE(&buffer_ptr->bentry[buffer_index], *page); 
}

int DELETE_PAGE_FROM_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index){
    if(buffer_ptr == NULL || buffer_index < 0 || buffer_index >= buffer_ptr->bsize) return 0;

    return EMPTY_PAGE(&buffer_ptr->bentry[buffer_index]);
}

int DELETE_BUFFER(buffer_t* buffer_ptr){
    if(buffer_ptr == NULL) return 0;

    for(buffer_size_t i = 0; i < buffer_ptr->bsize; i++)
        free(&buffer_ptr[i]->bentry);

    free(buffer_ptr);

    return 1;
}




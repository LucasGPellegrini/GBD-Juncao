#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "page.h"

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr){
    if(buffer_ptr == NULL || bsize <= 0) return 0;

    buffer_ptr = malloc(sizeof(buffer_t));
    if(buffer_ptr == NULL) return 0;

    buffer_ptr->bsize = bsize;

    page_t empty;
    EMPTY_PAGE(&empty);

    for(buffer_size_t i = 0; i < bsize; i++){
        buffer_ptr->bslots[i] = malloc(sizeof(buffer_slot_t));
        if(buffer_ptr->bslots[i] == NULL){
            for(buffer_size_t j = 0; j < i; j++){
                free(buffer_ptr->bslots[j]);
                free(buffer_ptr);
                return 0;
            }
        }

        buffer_ptr->bslots[i]->busage = NOT_IN_USE;
        EMPTY_PAGE(&buffer_ptr->bslots[i]);
    }

    return 1;
}

int FIND_FIRST_UNUSED_SLOT(buffer_t* buffer_ptr, buffer_slot_t* first_slot_ptr, buffer_size_t* first_slot_index){
    if(buffer_ptr == NULL || first_slot_ptr == NULL) return 0;

    for(buffer_size_t i = 0; i < buffer_ptr->bsize && buffer_ptr->bslots[i]->busage == IN_USE; i++);

    if(i == buffer_ptr->bsize) return 0;

    *first_slot_ptr = buffer_ptr->bslots[i];
    *first_slot_index = i;

    return 1;
}

// Warning: it does overwrite buffers page
int ADD_PAGE_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, page_type_t page_type, FILE* fp, long int offset){
    if(buffer_ptr == NULL || buffer_index < 0 || buffer_index >= buffer_ptr->bsize || page == NULL || !VALID_PAGE_TYPE(page->ptype) || fp == NULL || offset < 0) return 0;

    return COPY_TO_PAGE(&buffer_ptr->bentry[buffer_index], page_type, fp, offset); 
}

int ADD_BLOCK_TO_BUFFER(buffer_t* buffer_ptr, page_type_t page_type, FILE* fp, page_value_t first_page_of_block, page_value_t last_page_of_block){
    if(buffer_ptr == NULL || !VALID_PAGE_TYPE(page_type) || fp == NULL || first_page_of_block < 0 || last_page_of_block < first_page_of_block) return 0;

    page_value_t pval;
    PAGES_PER_FILE(fp, page_type, &pval);

    buffer_size_t number_of_pages_block = last_page_of_block - first_page_of_block;

    if(first_page_of_block >= pval || number_of_pages_block > buffer_ptr->bsize) return 0;

    for(buffer_size_t bindex, page_value_t i = first_page_of_block; i < last_page_of_block; i++)
        if(!ADD_PAGE_TO_BUFFER(buffer_ptr, bindex, page_type, fp, PAGE_SIZE * i)) return 0;

    return 1;
}

int ADD_FILE_TO_BUFFER(buffer_t* buffer_ptr, page_type_t page_type, FILE* fp){
    if(buffer_ptr == NULL || !VALID_PAGE_TYPE(page_type) || fp == NULL) return 0;

    page_value_t pval;

    PAGES_PER_FILE(fp, page_type, &pval);

    if(pval > buffer_ptr->bsize) return 0;

    for(page_value_t i = 0; i < pval; i++)
        if(!ADD_PAGE_TO_BUFFER(buffer_ptr, i, page_type, fp, PAGE_SIZE * i)) return 0;

    return 1;
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




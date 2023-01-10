#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int CREATE_BUFFER(buffer_size_t bsize, buffer_t* buffer_ptr){
    if(buffer_ptr == NULL || bsize <= 0) return 0;

    buffer_ptr = malloc(sizeof(buffer_t));
    if(buffer_ptr == NULL) return 0;

    buffer_ptr->bsize = bsize;

    for(buffer_size_t i = 0; i < bsize; i++){
        buffer_ptr->bentry[i] = malloc(sizeof(buffer_entry_t));
        if(buffer_ptr->bentry[i] == NULL){
            for(buffer_size_t j = 0; j < i; j++){
                free(buffer_ptr->bentry[j]);
                free(buffer_ptr);
                return 0;
            }
        }

        buffer_ptr->bentry[i].btype = VAZIO;
    }

    return 1;
}

int ADD_PAG_TO_BUFFER(buffer_t* buffer_ptr, buffer_size_t buffer_index, buffer_entry_type_t* pag, pagina_type_t pag_type){
    if(buffer_ptr == NULL || buffer_index < 0 || pag == NULL || !VALID_PAG_TYPE(pag_type)) return 0;

    
        
}
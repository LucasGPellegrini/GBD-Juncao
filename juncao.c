#include "juncao.h"
#include "arquivo.h"

int JUNCAO_ANIN_BLOC(FILE* fpr, entry_type_t rtype, FILE* fps, entry_type_t stype, buffer_size_t bsize){
    if(fpr == NULL || fps == NULL || !VALID_ENTRY_TYPE(rtype) || !VALID_ENTRY_TYPE(stype) || bsize <= 0) return 0;

    buffer_t buffer;
    if(!CREATE_BUFFER(bsize, &buffer)) return 0;

    entry_value_t rval;

    if(!ENTRIES_PER_FILE(fpr, rtype, &rval)) return 0;

    if(rval < buffer.bsize){
        if(!ADD_FILE_TO_BUFFER(&buffer, rtype, fpr)){
            DELETE_BUFFER(&buffer);
            return 0;
        }

        
    }
}
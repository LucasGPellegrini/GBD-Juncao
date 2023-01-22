#ifndef JUNCAO_H_INCLUDED
#define JUNCAO_H_INCLUDED

#include "registro.h"
#include "pagina.h"
#include "buffer.h"
#include "resultado.h"

int JOIN(FILE* fpr, entry_type_t rtype, FILE* fps, entry_type_t stype, buffer_size_t bsize, list_t* join_result);

#endif

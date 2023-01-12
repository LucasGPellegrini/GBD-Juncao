#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include "size.h"
#include "registro.h"
#include "page.h"

int FILE_SIZE(FILE* fp, memory_size_t* fsize);
int ENTRIES_PER_FILE(FILE* fp, entry_type_t etype, entry_value_t* eval);
int PAGES_PER_FILE(FILE* fp, entry_type_t etype, page_value_t* pval);

#endif
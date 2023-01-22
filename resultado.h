#ifndef RESULTADO_H_INCLUDED
#define RESULTADO_H_INCLUDED

#include "registro.h"
#include "pagina.h"

typedef struct join_t{
    void* rentry;
    entry_type_t rtype;
    void* sentry;
    entry_type_t stype;
} join_t;

typedef struct node_t{
   join_t* info;
   struct node_t* next;
} node_t;

typedef node_t* list_t;

int CREATE_ELEM(page_entry_t* rpage, page_value_t rentry, entry_type_t rtype, page_entry_t* spage, page_value_t sentry, entry_type_t stype, join_t** elem);
int DELETE_ELEM(join_t* elem);
list_t CREATE_LIST(void);
int EMPTY_LIST(list_t lst);
int INSERT_AT_END(list_t* lst, join_t* elem);
int EMPTY_THE_LIST(list_t* lst);
int DELETE_LIST(list_t* lst);
int SIZE(list_t lst);
void PRINT_LIST(list_t lst);



#endif
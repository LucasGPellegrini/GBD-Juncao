#include <stdlib.h>
#include <string.h>
#include "resultado.h"
#include "registro.h"

int CREATE_ELEM(page_entry_t* rpage, page_value_t rentry, entry_type_t rtype, page_entry_t* spage, page_value_t sentry, entry_type_t stype, join_t** elem){
    if(rpage == NULL || rentry < 0 || !VALID_ENTRY_TYPE(rtype) || sentry < 0 || !VALID_ENTRY_TYPE(stype) || elem == NULL || *elem == NULL)
        return 0;

    *elem = malloc(sizeof(join_t));
    if(*elem == NULL) return 0;

    join_t* join_ptr = *elem;

    join_ptr->rtype = rtype;
    join_ptr->stype = stype;

    switch(rtype){
        case ALUNO_PAGE:
            join_ptr->rentry = malloc(sizeof(aluno_t));
            if(join_ptr->rentry == NULL){
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->rentry, &rpage->alunos[rentry], sizeof(aluno_t));
            break;

        case CURSO_PAGE:
            join_ptr->rentry = malloc(sizeof(curso_t));
            if(join_ptr->rentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->rentry, &rpage->cursos[rentry], sizeof(curso_t));
            break;
    }

    switch(stype){
        case ALUNO_PAGE:
            join_ptr->sentry = malloc(sizeof(aluno_t));
            if(join_ptr->sentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr->sentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->sentry, &spage->alunos[sentry], sizeof(aluno_t));
            break;

        case CURSO_PAGE:
            join_ptr->sentry = malloc(sizeof(curso_t));
            if(join_ptr->rentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr->sentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->sentry, &spage->cursos[sentry], sizeof(curso_t));
            break;
    }

    return 1;
}

int DELETE_ELEM(join_t* elem){
    if(elem == NULL) return 0;

    free(elem->rentry);
    free(elem->sentry);
    free(elem);

    return 1;
}

list_t CREATE_LIST(){
    return NULL;
}

int EMPTY_LIST(list_t lst){
    return(lst == NULL);
}

int INSERT_AT_END(list_t* lst, join_t* elem){
    if(lst == NULL)
        return 0;

   list_t node = (list_t)malloc(sizeof(node_t));
    if(node == NULL)
        return 0;

   node->info = elem;

    if(EMPTY_LIST(*lst)){
        node->next = node;
        *lst = node;
    }else{
        node->next = (*lst)->next;
        (*lst)->next = node;
        *lst = node;
    }
    return 1;
}

int EMPTY_THE_LIST(list_t* lst){
    if(lst == NULL)
        return 0;

    if(EMPTY_LIST(*lst))
        return 1;

    list_t aux = (*lst)->next;
    list_t aux2;

    while(aux != *lst){
        aux2 = aux->next;
        DELETE_ELEM(aux->info);
        free(aux);
        aux = aux->next;
    }
    free(aux);
    *lst = NULL;

    return 1;
}

int DELETE_LIST(list_t* lst){
    return(EMPTY_THE_LIST(lst));
}

int SIZE(list_t lst){
    if(EMPTY_LIST(lst))
        return 0;

    int size = 1;
    list_t aux = lst->next;
    while(aux != lst){
        aux = aux->next;
        size++;
    }

    return size;
}


void PRINT_LIST(list_t lst){
    if(EMPTY_LIST(lst)){
        printf("Empty list!");
    }else{
        list_t head = lst;

        while(lst != head){
            printf("<\n");
            PRINT_ENTRY(&lst->info->rentry, lst->info->rtype);
            printf(",\n");
            PRINT_ENTRY(&lst->info->rentry, lst->info->stype);
            printf(">.");
        }
    }
}

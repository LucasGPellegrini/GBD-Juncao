#include <stdlib.h>
#include "resultado.h"
#include "registro.h"

int CREATE_ELEM(void* rentry, entry_type_t rtype, void* sentry, entry_type_t stype, joint_t** elem){
    if(rentry == NULL || !VALID_ENTRY_TYPE(rtype) || sentry == NULL || !VALID_ENTRY_TYPE(stype) || elem == NULL)
        return 0;

    *elem = malloc(sizeof(join_t));
    if(*elem == NULL) return 0;

    join_t* join_ptr = *elem;

    join_ptr->rtype = rtype;
    join_ptr->stype = stype;

    switch(rtype){
        case ALUNO:
            join_ptr->rentry = malloc(sizeof(struct aluno));
            if(join_ptr->rentry == NULL){
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->rentry, rentry, sizeof(struct aluno));
            break;

        case CURSO:
            join_ptr->rentry = malloc(sizeof(struct curso));
            if(join_ptr->rentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->rentry, rentry, sizeof(struct curso));
            break;
    }

    switch(stype){
        case ALUNO:
            join_ptr->sentry = malloc(sizeof(struct aluno));
            if(join_ptr->sentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr->sentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->sentry, sentry, sizeof(struct aluno));
            break;

        case CURSO:
            join_ptr->sentry = malloc(sizeof(struct curso));
            if(join_ptr->rentry == NULL){
                free(join_ptr->rentry);
                free(join_ptr->sentry);
                free(join_ptr);
                return 0;
            }

            memcpy(join_ptr->sentry, sentry, sizeof(struct curso));
            break;
    }

    return 1;
}

int DELETE_ELEM(join_t* elem){
    if(elem == NULL) return 0;

    free((*elem)->rentry);
    free((*elem)->sentry);
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
      free(aux->rentry);
      free(aux->sentry);
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
            PRINT_ENTRY(lst->info, lst->rtype);
            printf(",\n");
            PRINT_ENTRY(lst->info, lst->stype);
            printf(">.");
        }
    }
}

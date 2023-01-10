#include "pagina.h"

int VALID_PAG_TYPE(pagina_type_t pag_type){
    return pag_type == 'v' || pag_type == 'a' || pag_type == 'c';
}
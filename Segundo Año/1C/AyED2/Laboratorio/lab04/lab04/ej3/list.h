#include <stdbool.h>

#ifndef _LIST_H
#define _LIST_H

typedef int elem;
typedef struct s_node_t * list;

/* crea una lista vacía */
list empty(void);

/* agrega el elemento al comienzo de la lista l */
list addl(elem e, list l);

/* libera memoria en caso que sea necesario */
list destroy(list l);

/* devuelve true si l es vacía */
bool is_empty(list l);

/* devuelve el primer elemento de la lista l 
PRE: !is_empty(l)
*/
elem head(list l);

/* elimina el primer elemento de la lista l 
PRE: !is_empty(l)
*/
list tail(list l);

/* agrega el elemento al final de la lista l */
list addr(list l, elem e);

/* devuelve la cantidad de elementos de la lista l */
unsigned int length(list l);

/* agrega al final de l todos los elementos de l0 en el mismo orden */
list concat(list l, list l0);

/* devuelve el n-ésimo elemento de la lista l 
PRE: length(l) > n 
*/
elem index(list l, unsigned int n);

/* deja en l solo los primeros n elementos, eliminando el resto */
list take(list l, unsigned int n);

/* elimina los primeros n elementos de l */
list drop(list l, unsigned int n);

/* copia todos los elementos de l1 en la nueva lista l2 */
list copy_list(list l1);

#endif
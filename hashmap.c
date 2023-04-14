#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    long indice = hash(key,map->capacity);
    while (map->buckets[indice]!=NULL && map->buckets[indice]->key!=NULL)
    {
        if (is_equal(key,map->buckets[indice]->key)==1)return;
        indice=(indice+1)%map->capacity;    
    }
    map->buckets[indice]=createPair(key,value);
    map->current=indice;
    map->size++;
    return;
}
/*
Implemente la función void enlarge(HashMap * map). Esta función agranda la capacidad del arreglo buckets y reubica todos sus elementos. Para hacerlo es recomendable mantener referenciado el arreglo *actual/antiguo* de la tabla con un puntero auxiliar. Luego, los valores de la tabla se reinicializan con un nuevo arreglo con el **doble de capacidad**. Por último los elementos del arreglo antiguo se insertan en el mapa *vacío* con el método *insertMap*.
Puede seguir los siguientes pasos:

a - Cree una variable auxiliar de tipo Pair** para matener el arreglo map->buckets (*old_buckets*);

b - Duplique el valor de la variable capacity.

c - Asigne a map->buckets un nuevo arreglo con la nueva capacidad.

d - Inicialice size a 0.

e - Inserte los elementos del arreglo *old_buckets* en el mapa (use la función insertMap que ya implementó).
*/

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair** viejos=map->buckets;
    long capacidadVieja=map->capacity;
    map->capacity = map->capacity * 2;
    map->buckets = (Pair **) calloc(map->capacity,sizeof(Pair *));
    if (map->buckets==NULL)exit(EXIT_FAILURE);
    map->size=0;

    for (long k=0;k<capacidadVieja;k++)
    {
        if (viejos->buckets[k] != NULL && viejos->buckets[k]->key != NULL)
        {
            insertMap(map,viejos[k]->key,viejos[k]->value);
        }
            
    }
    free(viejos);
}

HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    if (map==NULL)return NULL;
    map->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
    if (map->buckets==NULL)return NULL;
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}
/* Implemente la función void eraseMap(HashMap * map,  char * key). Está función elimina el dato correspondiente a la clave key. Para hacerlo debe buscar el dato y luego *marcarlo* para que no sea válido.
**No elimine el par**, sólo invalídelo asignando NULL a la clave (pair->key=NULL).
Recuerde actualizar la variable size.
*/

void eraseMap(HashMap * map,  char * key) {    
    if (searchMap(map,key)!=NULL)
    {
        map->buckets[map->current]->key=NULL;
        map->size--;
        return;
    }
    

}

Pair * searchMap(HashMap * map,  char * key) {   
    long indice = hash(key,map->capacity);
    while (map->buckets[indice]!=NULL)
    {
        if (is_equal(key,map->buckets[indice]->key))
        {
            map->current=indice;
            return map->buckets[indice];
        }
        indice=(indice+1)%map->capacity;    
    }
    return NULL;
}

/*
    Implemente las funciones para recorrer la estructura: Pair * firstMap(HashMap * map) retorna el primer **Pair** válido del arreglo buckets. Pair * nextMap(HashMap * map) retorna el siguiente **Pair** del arreglo buckets a partir índice current. Recuerde actualizar el índice.*/
Pair * firstMap(HashMap * map) {
    for (size_t k=0;k<map->capacity;k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
            
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    for (size_t k=map->current+1;k<map->capacity;k++)
    {
        if (map->buckets[k] != NULL && map->buckets[k]->key != NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
    }
    return NULL;
}

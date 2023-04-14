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

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


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
    for (size_t k=0;k<map->size;k++)
    {
        if (map->buckets[k]!=NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
            
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    size_t k=map->current;
   while(k<map->size)
    {
        if (map->buckets[k]!=NULL)
        {
            map->current=k;
            return map->buckets[k];
        }
        k=(k+1)%map->capacity;
    }
    return NULL;
}

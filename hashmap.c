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

void eraseMap(HashMap * map,  char * key) {    


}
/*
Implemente la función Pair * searchMap(HashMap * map,  char * key), la cual retorna el **Pair** asociado a la clave ingresada. 
Recuerde que para buscar el par debe:

a - Usar la función hash para obtener la posición donde puede encontrarse el par con la clave

b - Si la clave no se encuentra avance hasta encontrarla (*método de resolución de colisiones*)

c - Si llega a una casilla nula, retorne NULL inmediatamente (no siga avanzando, la clave no está)

Recuerde actualizar el índice current a la posición encontrada.
Recuerde que el arreglo es **circular**.
*/
Pair * searchMap(HashMap * map,  char * key) {   
    long indice = hash(key,map->capacity);
    if (is_equal(key,map->buckets[indice]->key)==1)
    {
        map->current=indice;
        return map->buckets[indice];
    }
    while (map->buckets[indice]!=NULL)
    {
        if (is_equal(key,map->buckets[indice]->key)==1)
        {
            map->current=indice;
            return map->buckets[indice];
        }
        indice=(indice+1)%map->capacity;    
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}

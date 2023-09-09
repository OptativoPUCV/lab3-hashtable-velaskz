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
    
    long posicion = hash(key, map->capacity);

    if (map->buckets[posicion] == NULL || map->buckets[posicion]->key == NULL) {
        map->size++;
        Pair* nuevoPair = createPair(key, value);

        if (nuevoPair == NULL) {
            free(nuevoPair);
            return;
        }

        nuevoPair->value = value;
        nuevoPair->key = key;
        map->buckets[posicion] = nuevoPair;
    } else {
 
        long siguientePosicion = (posicion + 1) % map->capacity;
        while (siguientePosicion != posicion) {
            if (map->buckets[siguientePosicion] == NULL || map->buckets[siguientePosicion]->key == NULL) {
                map->size++;
                Pair* nuevoPair = createPair(key, value);

                if (nuevoPair == NULL) {
                    free(nuevoPair);
                    return;
                }

                nuevoPair->value = value;
                nuevoPair->key = key;
                map->buckets[siguientePosicion] = nuevoPair;
                break;
            }
            siguientePosicion = (siguientePosicion + 1) % map->capacity;
        }
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    
    long nuevaCapacidad = map->capacity * 2;
    
    Pair **nuevoBuckets = (Pair **)calloc(nuevaCapacidad, sizeof(Pair *));
    
    if (nuevoBuckets == NULL) {
        return;
    }

    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {

            long nuevaPosicion = hash(map->buckets[i]->key, nuevaCapacidad);
            nuevoBuckets[nuevaPosicion] = map->buckets[i];
        }
    }

    free(map->buckets);

    map->capacity = nuevaCapacidad;
    map->buckets = nuevoBuckets;
    
}

HashMap * createMap(long capacity) {
    
    HashMap* nuevoMapa = (HashMap*)malloc(sizeof(HashMap));
    
    if (nuevoMapa != NULL) {
        
        nuevoMapa->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);
        
        if (nuevoMapa->buckets == NULL){
            free(nuevoMapa);
            return NULL;
        }
    }

    nuevoMapa->size = 0;
    nuevoMapa->capacity = capacity;
    nuevoMapa->current = -1;
    
    return nuevoMapa;
}

void eraseMap(HashMap * map,  char * key) {    

    Pair *pair = searchMap(map, key);

    if (pair != NULL){
        free(pair->key);
        pair->key = NULL;
        map->current = -1;
        map->size--;
    }
    
}

Pair * searchMap(HashMap * map,  char * key) {   

    long posicion = hash(key, map->capacity);
    long initialPos = posicion; 

    do {
        if (map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL) {
            if (is_equal(map->buckets[posicion]->key, key) {

                map->current = posicion;
                return map->buckets[posicion];
            }
        }

        posicion = (posicion + 1) % map->capacity;
    } while (posicion != initialPos);  

    map->current = -1;
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for (long i = 0; i < map->capacity; i++) {
        
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    
    map->current = -1;
    return NULL;
}

Pair * nextMap(HashMap * map) {

    if (map->current >= 0 && map->current < map->capacity) {

        for (long i = map->current + 1; i < map->capacity; i++) {
            if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {

                map->current = i;
                return map->buckets[i];
            }
        }
    }
    
    map->current = -1;
    return NULL;
}
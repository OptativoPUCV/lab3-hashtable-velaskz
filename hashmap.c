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

    float load_factor = (float)map->size / map->capacity;

    if (load_factor > 0.7) {
        long viejaCapacidad = map->capacity;
        Pair **viejoBuckets = map->buckets;

        map->capacity = viejaCapacidad * 2;

        Pair **nuevoBuckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);

        if (nuevoBuckets == NULL) {

            return;
        }

        for (long i = 0; i < map->capacity; i++) {
            nuevoBuckets[i] = NULL;
        }

        for (long i = 0; i < viejaCapacidad; i++) {
            if (viejoBuckets[i] != NULL && viejoBuckets[i]->key != NULL) {

                long nuevaPosicion = hash(viejoBuckets[i]->key, map->capacity);

                nuevoBuckets[nuevaPosicion] = viejoBuckets[i];
            }
        }

        free(viejoBuckets);
        map->buckets = nuevoBuckets;
    }

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

    long posicion = hash(key, map->capacity);
    long initialPos = posicion; .

    do {
        if (map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL) {
            if (strcmp(map->buckets[posicion]->key, key) == 0) {
            
                free(map->buckets[posicion]);
                map->buckets[posicion] = NULL;
                map->current = -1;
                map->size--;
                return;
            }
        }

        posicion = (posicion + 1) % map->capacity;
    } while (posicion != initialPos);  
}

Pair * searchMap(HashMap * map,  char * key) {   

    long posicion = hash(key, map->capacity);
    long initialPos = posicion; 

    do {
        if (map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL) {
            if (strcmp(map->buckets[posicion]->key, key) == 0) {

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

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
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

        // Calcula el factor de carga actual.
    float load_factor = (float)map->size / map->capacity;

    if (load_factor > 0.7) {
        // Hora de expandir.
        long old_capacity = map->capacity;
        Pair **old_buckets = map->buckets;

        // Duplica la capacidad.
        map->capacity = old_capacity * 2;

        // Crea un nuevo arreglo de buckets con la nueva capacidad.
        Pair **new_buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);

        if (new_buckets == NULL) {
            // Manejo de error: no se pudo asignar memoria para el nuevo arreglo.
            return;
        }

        // Inicializa todos los buckets en el nuevo arreglo a NULL.
        for (long i = 0; i < map->capacity; i++) {
            new_buckets[i] = NULL;
        }

        // Recorre el antiguo arreglo de buckets y reinserta los elementos en el nuevo.
        for (long i = 0; i < old_capacity; i++) {
            if (old_buckets[i] != NULL && old_buckets[i]->key != NULL) {
                // Calcula la nueva posición para el par clave-valor en el nuevo arreglo.
                long new_position = hash(old_buckets[i]->key, map->capacity);

                // Inserta el par clave-valor en la nueva posición.
                new_buckets[new_position] = old_buckets[i];
            }
        }

        // Libera el antiguo arreglo de buckets y actualiza el hashmap.
        free(old_buckets);
        map->buckets = new_buckets;
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
    

}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
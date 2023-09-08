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

    if (map->buckets[posicion] == NULL) {
        // No hay colisión en este bucket, creamos un nuevo Pair y lo asignamos directamente
        Pair * nuevoPair = createPair(key, value);

        if (nuevoPair == NULL) {
            // Manejo de error si no se puede crear el nuevo Pair
            free(nuevoPair);
            return;
        }

        map->buckets[posicion] = nuevoPair;
        map->size++;
    } else {
        // Hay una colisión, manejaremos esto usando listas enlazadas
        Pair * current = map->buckets[posicion];
        Pair * prev = NULL;

        // Buscamos si la clave ya existe en la lista enlazada
        while (current != NULL) {
            if (is_equal(current->key, key)) {
                // La clave ya existe, actualizamos el valor
                current->value = value;
                return;
            }
            prev = current;
            current = current->next;
        }

        // La clave no existe en la lista, creamos un nuevo Pair y lo agregamos al final de la lista
        Pair * nuevoPair = createPair(key, value);

        if (nuevoPair == NULL) {
            // Manejo de error si no se puede crear el nuevo Pair
            free(nuevoPair);
            return;
        }

        prev->next = nuevoPair;
        map->size++;
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


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
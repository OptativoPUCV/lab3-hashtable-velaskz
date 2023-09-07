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
    
    if (map->buckets[posicion] == NULL || map->buckets[posicion]->key == NULL){

        map->size++;
        Pair* nuevoPair = createPair(key, value);
        
        if(nuevoPair == NULL){
            free(nuevoPair);
            return;
        }

        nuevoPair->value = value;
        nuevoPair->key = key;
        map->buckets[posicion] = nuevoPair;
        
        //recorrer el mapa hasta encontrar un aposición vacía
        //posición++
    }else {
        // La posición ya está ocupada, podemos manejar esto de varias maneras,
        // una opción podría ser implementar una estrategia de manejo de colisiones,
        // como encadenamiento o sondeo lineal. Por ejemplo, podríamos buscar la
        // siguiente posición disponible en el arreglo y colocar el par clave-valor allí.
        // Esto depende de la estrategia de manejo de colisiones que desees implementar.

        // Ejemplo de sondeo lineal (busca la siguiente posición vacía):
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

/* The single most stupid mapping object interface EVER WRITTEN.
 * f03lipe, 2013.
 */


#include <stdio.h>
#include <stdlib.h>


/* Alphabet size. */
#define MAPS_MAX 26


typedef struct {
	int keys[MAPS_MAX];
	int values[MAPS_MAX];
} MapObj;

copyMapObj(MapObj * dest, MapObj * source) {
freeMapObj(MapObj * map) {


/* The single most stupid mapping object interface EVER WRITTEN.
 * f03lipe, 2013.
 */


#include "mapObj.h"


void freeMapObj(MapObj * map);

void printMap(MapObj * map);

MapObj * copyMapObj(MapObj * dest, MapObj * source);

MapObj * assignKey(MapObj * map, int key, char value);

char getValue(MapObj * map, int key);

char * mapToWord(char * buffer, MapObj * map, int * msg);
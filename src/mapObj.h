
/* The single most stupid mapping object interface EVER WRITTEN.
 * f03lipe, 2013.
 */


#include <stdio.h>
#include <stdlib.h>


#define MAPS_MAX 26 /* English alphabet size. */


typedef struct {
	int keys[MAPS_MAX];
	int values[MAPS_MAX];
} MapObj;



void freeMapObj(MapObj * map);

void printMap(MapObj * map);

MapObj * copyMapObj(MapObj * dest, MapObj * source);

MapObj * assignKey(MapObj * map, int key, char value);

char getValue(MapObj * map, int key);

char * mapToWord(char * buffer, MapObj * map, int * msg);
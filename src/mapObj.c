
/* The single most stupid mapping object interface EVER WRITTEN.
 * f03lipe, 2013.
 */


#include "mapObj.h"

/* MapObj interface */

MapObj *
copyMapObj(MapObj * dest, MapObj * source) {
/* Copies a mapping object from source to dest. */
	dest = memcpy(dest, source, sizeof(MapObj));
	return dest;
}


void
freeMapObj(MapObj * map) {
/* Frees the mapping object. Just calling free(map); is OK:
 * this is just for the sake of design. */
	free(map);
}


void
printMap(MapObj * map) {
/* Prints the mapping object. That's all. */
	int c;
	for (c=0; map->values[c]; c++)
		printf(".map[%d]: %c\n", map->keys[c], map->values[c]);
	printf("\n");
}


MapObj *
assignKey(MapObj * map, int key, char value) {
/* Basic `map[key] = value` operation. */
	int c;
	for (c=0; map->values[c] && map->keys[c] != key; c++)
		;
	map->keys[c] = key;
	map->values[c] = value;
	return map;
}


char 
getValue(MapObj * map, int key) {
/* Basic `map.get(key, -1)` operation. (-1 is returned when 404 :P)*/
	int c = 0;
	/* No hash algorithms here, sorry. :P */
	for (; map->keys[c]; c++) {
		if (map->keys[c] == key)
			return map->values[c];
	}
	return -1;
}


char *
mapToWord(char * buffer, MapObj * map, int * msg) {
/* Translates a map using a coded message and writes (and returns) to buffer. */
	int * p = msg;
	char * b = buffer;
	for (; *p && *p != -1; p++) {
		*b++ = getValue(map, *p);	
	}
	*b = '\0';
	return buffer;
}
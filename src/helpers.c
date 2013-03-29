
/* helper.c for github.com/f03lipe/decipher
 */

#include <stdio.h>
#include <stdlib.h>


void *cmalloc(size_t msize);

void quit(char *msg);

void printIntArray(int *ptr);

void printMessage(MapObj * map, int ** msgs);


void *
cmalloc(size_t msize)
/* Custom malloc to watch for failures while alloc memory. */
{
	void * p;
	char msg[15];

	if (!(p = calloc(msize, (size_t) 1))) {
		sprintf(msg, "malloc(%ld) failed", msize);
		quit(msg);
	}
	return p;
}


void
quit(char * msg)
/* Show message and quit. */
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}


void
printIntArray (int * ptr)
/* Until -1 is found. */
{
	printf("%d", *ptr++);
	for (; *ptr != -1; ptr++)
		printf(",%d", *ptr);
	printf("\n");
}


void
printMessage(MapObj * map, int ** msgs)
{
	char * word = cmalloc(50);
	printf("> ");
	for (; *msgs; msgs++) {
		word = mapToWord(word, map, *msgs);
		printf("%s ", word);
	}
	printf("\n");
	free(word);
}
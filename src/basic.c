
/* A basic 1:1 matcher written in C.
 * f03lipe, 2013.
 */


#include "basic.h"

/*  interface */

void *
cmalloc(size_t msize)
/* Custom malloc to watch for failures while alloc memory. */
{
	void * p;
	char msg[15];

	if (!(p = malloc(msize))) {
		sprintf(msg, "malloc(%ld) failed", msize);
		quit(msg);
	}
	return p;
}
//

int **
getEncodedWords(int * msgBuffer[])
{
	FILE * wordsfile;
	char * buffer;
	int  * msg;
	unsigned wsize,
			 mcount = 0;
	
	wordsfile = fopen(MSGS_FILE, "r");
	buffer = cmalloc(MAXL_MSGW);

	while (fgets(buffer, MAXL_MSGW, wordsfile))
	{
		/* Parse coded word and store. */

		wsize = strlen(buffer);
		wsize -= 1; /* Minus \n character. */
		msg = cmalloc(wsize*sizeof(int));
		msgBuffer[mcount++] = msg;

		do {
			/* Scan an integer from the line. */
			sscanf(buffer, "%d", msg);
			/* Skip digits before the comma. */
			while (*buffer && *buffer++ != ',')
				;
			msg++;
		} while (*buffer && *buffer != '\n');

		*msg = -1;
	}
	
	msgBuffer[mcount] = NULL;
	return msgBuffer;
}

char **
getDictWords(char * dictBuffer[])
{
	FILE * dictfile;
	char * buffer,
		 * word;
	unsigned wcount = 0, 
			 wsize;

	dictfile = fopen(DICT_FILE, "r");
	buffer = cmalloc(MAXL_WORD);
	
	while (fgets(buffer, MAXL_WORD, dictfile))
	{
		/* Hack to remove trailing \n characters. */
		wsize = strlen(buffer);
		buffer[wsize-1] = '\0';
		wsize -= 1;

		/* Allocate buffer `word` and store word. */
		word = cmalloc(wsize);
		word = strcpy(word, buffer);
		dictBuffer[wcount++] = word;
	}

	dictBuffer[wcount] = NULL;
	return dictBuffer;
}


void
match (MapObj * map)
{
	char ** word = dict;
	int	 * msg = *msgs;
	
	char h[50];
	mapToWord(h, map, msg);

	while (*(++word)) {
		// printf("> %s\n", *word);
		if (!strcmp(h, *word))
			printf("%s\n", h);
	}
	// printMap(map);
}


char *
splitAlphab(char * buffer, char * alphabet, int index)
/* Copies alphabet to buffer while popping the index-nth character. */
{
	char * temp;
	temp = cmalloc(strlen(alphabet)+1);
	strcpy(temp, alphabet);
	temp[index] = '\0';
	strcpy(buffer, temp);
	strcpy(buffer+index, temp+index+1);
	free(temp);
	return buffer;
}


void
combine(MapObj * map, int * symbols, char * alphabet)
{
	MapObj * nmap;
	char letter, * nalphab;
	int sym, index,	asize;

	if (symbols[0] == -1) {
		/* Try to match current word against the dictionary. */
		match(map);
		return;
	}  

	asize = strlen(alphabet);
	sym = symbols[0];
	nmap = copyMapObj(cmalloc(sizeof(MapObj)), map);

	for (index=0; index<asize; index++) {
		nalphab = splitAlphab(cmalloc(asize), alphabet, index);
		nmap = assignKey(nmap, sym, alphabet[index]);
		combine(nmap, symbols+1, nalphab);
	}

	freeMapObj(nmap);
}


int *
uniquefySymbols (int * buffer, int * symbols)
/* Fills buffer with unique items from symbols. */
{
	int * p = symbols,
		* p2,
		count = 0;
	
	for (p = symbols; *p != -1; p++) {
		for (p2 = symbols; p2 != p; p2++) {
			if (*p == *p2)
				break;
		}
		if (p == p2) {
			/* Symbol currently pointed by p wasn't found by p2:
			 * the loop didn't break. */
			buffer[count++] = *p;	
		}
	}
	buffer[count] = -1;
	return buffer;
}


void
quit(char * msg)
/* Show message and quit. */
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}


int
main(int argc, const char *argv[])
{
	MapObj * map;

	msgs = cmalloc(MAXS_MSGS*sizeof(char *));
	msgs = getEncodedWords(msgs);

	dict = cmalloc(MAXS_DICT*sizeof(char *));
	dict = getDictWords(dict);


	int * s = cmalloc(MAXL_WORD * sizeof(int));
	s = uniquefySymbols(s, msgs[0]);


	int c=0;
	do {
		printf("%d-", s[c]);
		c++;
	} while (s[c] != -1);
	puts("");

	map = cmalloc(sizeof(MapObj));
	combine(map, s, ALPHABET);

	return 0;
	return 0;	
	
	do {
		printf("%s\n", *dict);	
	} while (*++dict);

	return 0;
}


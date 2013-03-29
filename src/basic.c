
/* A basic substitution decipher written in C.
 * f03lipe, 2013.
 */


#include "basic.h"
#include "helpers.c"


int **
getEncodedMsg(int * msgBuffer[])
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
			if ((int) *msg <= 0) {
				char * str = malloc(30);
				sprintf(str,
					"All tokens must be positive integers. Invalid token: %d.",
					(int) *msg);
				quit(str);
			}
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

		/* `word = word.lower()` */
		for (; *word; word++)
			*word = tolower(*word);
	}
	dictBuffer[wcount] = NULL;
	return dictBuffer;
}


/****/


void
match(MapObj * map)
{
	int	 ** ptr, cmp;
	char ** wptr,
		 * word = cmalloc(50);

	for (ptr=msgs; *ptr; ptr++) {
		/* Loop through encoded message. */
		word = mapToWord(word, map, *ptr);
		// printMessage(map, msgs); 

		for (wptr=dict; *wptr; wptr++) {
			/* Loop through dictionary words. */
			cmp = strcmp(word, *wptr);
			if (!cmp || cmp < 0)
				break;
			// printf("> %s > %s, %d\n", word, *wptr, cmp);
		}
		if (cmp) 
			/* Word didn't match .*/
			goto RETURN;
		// printf("> %s\n", word);
	}
	printMessage(map, msgs); 

RETURN:
	free(word);
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

	free(nmap);
}

int *
uniquefySymbols (int * buffer, int ** msgs)
/* Fills buffer with unique items from msgs. */
{
	int * p,
		* p2,
		count = 0;
	for (; *msgs; msgs++) {
		/* Loop through all messages. */
		for (p = *msgs; *p != -1; p++) {
			for (p2 = buffer; *p2 != 0; p2++)
				if (*p == *p2)
					break;
			if (!*p2) {
				/* Symbol currently pointed by p wasn't found by p2:
				 * the loop didn't break. */
				buffer[count++] = *p;	
			}
		}
		buffer[count] = -1;
	}
	return buffer;
}



char ** dict;
int  ** msgs;

int
main(int argc, const char *argv[])
{
	MapObj * map;
	int * symbols;

	msgs = cmalloc(MAXS_MSGS*sizeof(char *));
	dict = cmalloc(MAXS_DICT*sizeof(char *));
	map = cmalloc(sizeof(MapObj));

	dict = getDictWords(dict);
	puts("Finished reading the dictionary.");
	msgs = getEncodedMsg(msgs);
	puts("Finished reading the encoded message.");

	symbols = uniquefySymbols(cmalloc(ALPHBSIZE*sizeof(int)), msgs);
	printf("The symbols found in the encoded message were ");
	printIntArray(symbols);
	
	combine(map, symbols, ALPHABET);

	free(msgs);
	free(dict);
	free(map);
	free(symbols);

	return 0;
}




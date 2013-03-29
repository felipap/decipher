
/* A basic 1:1 matcher written in C.
 * f03lipe, 2013.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapObj.c"


#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define ALPHBSIZE 26

#define DICT_FILE "dict/words"
#define MSGS_FILE "msgs.txt"

#define MAXS_DICT 100000
#define MAXS_MSGS 30
#define MAXL_WORD 30+1 /* Plus null terminator. */
#define MAXL_MSGW MAXL_WORD*3 /* One char seldom uses + than 2 digits + ','. */


char ** dict;
int  ** msgs;


int **getEncodedMsg(int * msgBuffer[]);

char **getDictWords(char * dictBuffer[]);

void match(MapObj * map);

char *splitAlphab(char * buffer, char * alphabet, int index);

void combine(MapObj * map, int * symbols, char * alphabet);

int *uniquefySymbols (int * buffer, int ** msgs);

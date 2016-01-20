#include <stdio.h>
#include <stdlib.h>
#include "path.h"

/*
* PURPOSE : Initialise a Path
*
* INPUTS :
*			Path *P:		pointer to path being initialised
*			int size:		max size of path
*
*/
void PathInit(Path *P, int size) {
	P->size = 0;
	P->maxsize = size;
	P->item = malloc(size*sizeof(int));
}

/*
* PURPOSE : Free all variables used by a Path
*
* INPUTS :
*			Path *P:		pointer to path being deconstructed
*
*/
void PathDestroy(Path *P) {
	free(P->item);
	free(P);
}

/*
* PURPOSE : Clones values from one path to another up to and including the specified last position
*			(if last position is not existent in the path, the entire path is copied)
*
* INPUTS :
*			Path *O:		pointer to original path
*			Path *P:		pointer to destination path
*			int lastPos:	last position to copy
*
*/
void PathClone(Path *O, Path *P, int lastPos) {
	int i = 0;
	for (i = 0; i < O->size; i++) {
		P->item[i] = O->item[i];
		if (P->item[i] == lastPos) {
			i++;
			break;
		}
	}
	P->size = i;

}

/*
* PURPOSE : Tries to add a position to a path
*
* INPUTS :
*			Path *P:		pointer to Path
*			int lastPos:	position to add
*
* RETURNS:	The new size or -1 if position already exists
* 
*/
int PathAddEntry(Path *P, int entry) {
	int i = 0;
	for (i = 0; i < P->size; i++) {
		if (P->item[i] == entry)
			return -1;
	}
	if (P->size + 1 > P->maxsize)
		printf("No more space to add to Path\n");
	P->item[P->size++] = entry;
	return P->size;
}

/*
* PURPOSE : Removes the last entry from a Path (similar to a Pop method)
*
* INPUTS :
*			Path *P:		pointer to Path
*
* RETURNS:	The removed position
*
*/
int PathRemoveEntry(Path *P) {
	P->size--;
	int x = P->item[P->size];
	P->item[P->size] = -1;
	return x;
}

/*
* PURPOSE : Print the path positions
*
* INPUTS :
*			Path *P:		pointer to Path
*
*/
void PathPrint(Path P) {
	int i = 0;
	for (i = 0; i < P.size; i++) {
		printf("%i ", P.item[i]);
	}
	printf("\n");
}
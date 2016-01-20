#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

/*
* PURPOSE : Free all variables used by a Vector
*
* INPUTS :
*			Vector *P:		pointer to Vector being deconstructed
*
*/
void VectorDestroy(Vector *V) {
	free(V->item);
	free(V);
}

/*
* PURPOSE : Get data for vector from stdin
*
* INPUTS :
*			Path *V:		pointer to Vector to be read into
*
*/
void VectorRead(Vector *V) {
    printf("Size of vector: ");
	char* _size = (char*)malloc(17 * sizeof(char));
    fgets(_size, 16, stdin);
    int size = atoi(_size);
	V->size = size;
    V->item = malloc(1 + size*sizeof(int));
    printf("Enter space separated values for the vector:\n");
	char* userInput = malloc(1025 * sizeof(int));
	fgets(userInput, 1024, stdin);
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < 1024; i++) {
		if (userInput[i] == '\n')
			break;
        char* _x = malloc(17 * sizeof(int));
		//Skip all spaces preceding the value
		while (userInput[i] < '0' || userInput[i] > '9')
            i++;
        j = 0;
		//Read the value one digit at a time
        while (userInput[i] > '0' && userInput[i] < '9')
            _x[j++] = userInput[i++];
        V->item[k++] = atoi(_x);
		free(_x);
    }
	free(userInput);
	free(_size);
}
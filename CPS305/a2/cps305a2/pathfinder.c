#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "path.h"

/*
* PURPOSE : Main recursive loop for the path finder
*
* INPUTS :  
*			int position:		the current position in the vector
*			Vector* V:			the vector being searched
*			Path* Solution:		the solutions array
*			int SolutionIndex:	the index (or id) of the solution currently being worked on
*
* NOTES :   When the finder encounters a situation where it can go forwards or backwards,
*			it will try to move forward and once that recursion call completes and returns,
*			it will continue to check (and if neccesary move) backwards. If it comes to a point
*			where no path (neither forward nor backward) was found it will print appropriate msg.
*/
int AllPathsRec(int position, Vector* V, Path* Solution, int SolutionIndex) {
	//Tries to add current position to solution, if position has already been visited then
	//	simply returns out of the current solution because it is a dead end
	if (PathAddEntry(&Solution[SolutionIndex], position) == -1)
		return;
	int value = V->item[position];
	if (value == 0) {
		PathPrint(Solution[SolutionIndex]);
		return 0;
	}
	int pathCounter = 0;
	if (position + value < V->size) { //If can forward, move forward
		pathCounter++;
		AllPathsRec(position + value, V, Solution, SolutionIndex);
	}
	if (position - value > 0) { //If can backward, move backward
		pathCounter++;
		// If has already moved forward (and completed) this solution, create a new solution
		// at current position
		if (pathCounter > 1) {
			PathClone(&Solution[SolutionIndex], &Solution[SolutionIndex + 1], position);
			AllPathsRec(position - value, V, Solution, SolutionIndex + 1);
		}
		else //otherwise just regular move backwards
			AllPathsRec(position - value, V, Solution, SolutionIndex);
	}
	if (pathCounter == 0) {
		printf("No path.\n");
		return -1;
	}

}

int main(int argc, char* argv[]) {
	Vector* V = malloc(sizeof(Vector));
    VectorRead(V);
	Path* Solution = malloc(1024*sizeof(Path));
	int i = 0;
	for (i = 0; i < 1024; i++) {
		PathInit(&Solution[i], V->size);
	}
	AllPathsRec(0, V, Solution, 0);
	PathDestroy(Solution);
	VectorDestroy(V);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int real;
    int imag;
} Complex;

/*
* PURPOSE : Print stats for the game
*
* INPUTS :  Total number of answers and counters for the 3 types of answers
*				
* NOTES :   If total answers <= 0, no percentages will be calculated
*/
void printStats(int iteratorCounter, int correctFirstTime, int correctNTime, int correctWithHints) {
    if (iteratorCounter > 0) {
        correctFirstTime = (int)((double)correctFirstTime / iteratorCounter * 100);
        correctNTime = (int)((double)correctNTime / iteratorCounter * 100);
        correctWithHints = (int)((double)correctWithHints / iteratorCounter * 100);
    }

    printf("----------------------\n");
    printf("%d\t Total number\n", iteratorCounter);
    printf("%d%%\t Correct first time (no hints)\n", correctFirstTime);
    printf("%d%%\t Correct after 2 or more guesses (no hints)\n", correctNTime);
    printf("%d%%\t Correct after hint(s)\n", correctWithHints);
    printf("----------------------\n");
}

/*
* PURPOSE : Print hints to help the user
*
* INPUTS :  int hCount:     type of hint
*           Complex** c:    the array from which to print addresses
*           int N:          the size of the array
*/
void showHints(int hCount, Complex** c, int N) {
    int i, j;
    switch (hCount) {
    case 1:
        for (i = 0; i < N; i++) {
            printf("M[%d][%d] %p\n", i, 0, &c[i][0]);
        }
        break;
    case 2:
        for (i = 0; i < N; i++) {
            printf("\tM[%d][%d]\t", 0, i);
        }
        printf("\nM[0][0]");
        for (i = 0; i < N; i++) {
            printf("\t%p", &c[0][i]);
        }
        printf("\n");
        for (i = 0; i < N; i++) {
            printf("M[%d][%d] %p\n", i, 0, &c[i][0]);
        }
        break;
    case 3:
        for (i = 0; i < N; i++) {
            printf("\tM[%d][%d]\t", 0, i);
        }
        for (i = 0; i < N; i++) {
            printf("\nM[%d][%d] ", i, 0);
            for (j = 0; j < N; j++) {
                printf("%p\t", &c[i][j]);
            }
        }
        printf("\n");
        break;
    }
}

/*
* PURPOSE : Generates a dynamically allocated square 2D array of given size
*
* INPUTS :  size
*
* RETURNS: a reference to the origin of the created 2D array
*
*/
Complex** create2DComplexArray(int size) {
    Complex** result = (Complex**)malloc(size*sizeof(Complex*));
    int i, j;
    for (i = 0; i < size; i++)
        result[i] = (Complex*)malloc(size*sizeof(Complex));

    return result;
}

/*
* PURPOSE : Deallocate memory for given square array
*
* INPUTS :  Complex** c:   the 2D array to deallocate
*           int N:      the size of the array
*
*/
void free2DArray(Complex** c, int N) {
    int i = 0;
    for (i = 0; i < N; i++) {
        free(c[i]);
    }
    free(c);
}

/*
* PURPOSE : Parse userinput into 2 ints
*
* INPUTS :  char* userInput:   string containing user input to parse
*           
* RETURNS : int* result:       returns a int[2] containing the 2 parsed numbers 
*/
int* parseGuess(char* userInput) {
    int* result = (int*)malloc(3 * sizeof(int));

    //Strings containing the 2 numbers the user guessed for the coordinates
    char* _x = (char*)malloc(16 * sizeof(char));
    char* _y = (char*)malloc(16 * sizeof(char));
    int i = 0,
        j = 0;
    int maxInput = 35;
    while ((userInput[i] < '0' && userInput[i] > '9') && i < maxInput) {
        i++;
    }
    if (i == maxInput) { //Nothing was entered
        result[0] = result[1] = -1;
        return result;
    }
    while ((userInput[i] >= '0' && userInput[i] <= '9') && i < maxInput) {
        _x[i] = userInput[i];
        i++;
    }
    while ((userInput[i] < '0' || userInput[i] > '9') && i < maxInput) {
        i++;
    }
    j = i;
    while ((userInput[i] >= '0' && userInput[i] <= '9') && i < maxInput) {
        _y[i - j] = userInput[i];
        i++;
    }

    //Parsed integers of the user input
    int x = atoi(_x);
    int y = atoi(_y);

    free(_x);
    free(_y);

    result[0] = x;
    result[1] = y;
    return result;
}

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    int N = 5;
    if (argc > 1) 
        N = atoi(argv[1]);
    
    int i, j; //To be used in future loops

    Complex** c = create2DComplexArray(N);
    
    //Counters for stats:
    int correctFirstTime = 0,
        correctNTime = 0,
        correctWithHints = 0;

    //Main loop1:
    int iteratorCounter1 = 1,
        maxIterations1 = 1000000; //To guarantee no infinite loops
    do {
        int x = rand() % N,
            y = rand() % N;

        Complex* c_Origin = &c[0][0];
        Complex* c_Selected = &c[x][y];

        int hintsUsed = 0;

        //Main loop2:
        int iteratorCounter2 = 1,	
            maxIterations2 = 1000000; //To guarantee no infinite loops
        do {
            printf("M[0][0]=%p. M[i][j]=%p. What's i and j? (or Q or H or HH or HHH): ", c_Origin, c_Selected);

            char* userInput = malloc(36 * sizeof(char));
            fgets(userInput, 36, stdin);
            if (userInput[0] == 'Q' || userInput[0] == 'q') {
                free(userInput);
                goto exit;
            }
            else if (userInput[0] == 'H' || userInput[0] == 'h') {
                int hCount = 0;
                for (i = 0; i < 32; i++) {
                    if (userInput[i] == 'H' || userInput[i] == 'h')
                        hCount++;
                    else break;
                }
                free(userInput);
                hintsUsed++;
                showHints(hCount, c, N);
            }
            else
            {
                int* parsedResult = parseGuess(userInput);
                int _x = parsedResult[0];
                int _y = parsedResult[1];
                free(parsedResult);
                free(userInput);
                if (_x == -1 || y == -1)
                    continue;
                if (x == _x && y == _y) {
                    printf("RIGHT\n");
                    if (hintsUsed > 0)
                        correctWithHints++;
                    else if (iteratorCounter2 > 1)
                        correctNTime++;
                    else
                        correctFirstTime++;
                    break;
                }
                else
                {
                    printf("WRONG\n");
                    continue;
                }
            }
        } while (iteratorCounter2++ < maxIterations2);
    } while (iteratorCounter1++ < maxIterations1);

exit: 
    free2DArray(c, N);
    printStats(--iteratorCounter1, correctFirstTime, correctNTime, correctWithHints);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int getInput();

int main()
{
	getInput();
	return 0;
}

int getInput()
{
	int numSym;
	int numStates;
	int i;
	int j;
	int k;
	int *** matrix = NULL;
	printf("Number of Input Symbols: ");
	scanf(" %d", &numSym);
	printf("Number of States: ", &numSym);
	scanf(" %d", &numStates);
	if ((numSym < 1) || (numStates < 1)) {
		return 1;
	}
	
	//initialize matrix
	matrix = (int ***) malloc(numStates*sizeof(int **));
	for (i = 0; i < numStates; i++) {
		matrix[i] = (int **) malloc(numSym*sizeof(int *));
		for (j = 0; j < numSym; j++) {
			matrix[i][j] = (int *) malloc(numStates*sizeof(int));
			for (k = 0; k < numStates; k++) {
				matrix[i][j][k] = 0;
			}
		}
	}

	printf("\tepsilon");
	for (i = 1; i <= numSym; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	for (i = 0; i < numStates; i++) {
		printf("q%d", i);
		for (j = 0; j < numSym; j++) {
			printf("\t");
		}
		printf("\n");
	}
	return 0;
}
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int getStates(int * array);

int getInput(int **** matrix, int * countStates, int * countSymbols);

int display(int *** matrix, int numStates, int numSymbols);

int main()
{
	int *** matrix;
	int numStates;
	int numSymbols;
	getInput(&matrix, &numStates, &numSymbols);
	display(matrix, numStates, numSymbols);
	return 0;
}

int display(int *** matrix, int numStates, int numSymbols)
{
	int i;
	int j;
	int k;
	printf("NFA transition table\n");
	for(i = 0; i < numStates; i++) {
		printf("q%d", i);
		for(j = 0; j < numSymbols; j++) {
			printf("\t");
			for(k = 0; k < numStates; k++) {
				if(matrix[i][j][k] == 1) {
					printf("%d ", k);
				}
			}
		}
		printf("\n");
	}
	return 0;
}

int e_close(int *** matrix, int numSymbols, int numStates, int * states)
{
	int i;
	int j;
	int flag = 1;
	int * closure = (int *) malloc(numStates * sizeof(int));
	// initialize closure
	for (i = 0; i < numStates; i++) {
		closure[i] = 0;
	}
	// find closure
	while (flag) {
		flag = 0;
		for (i = 0; i < numStates; i++) {
			if (states[i] == 1) {
				flag = 1;
				for (j = 0; j < numStates; j++) {
					if (matrix[i][0][j] == 1) {
						if (states[j] == 0) {
							states[j] = 1;
						}
						closure[j] = 1;
					}
				}
				states[i] = 2;
			}
		}
	}
	//set output array to represent closure
	for (i = 0; i < numStates; i++) {
		if (states[i] == 2) {
			closure[i] = 1;
		}
		if (closure[i] == 1) {
			states[i] = 1;
		} else {
			states[i] = 0;
		}
	}
	free(closure);
	closure = NULL;
	return 0;
}

int getInput(int **** matrix, int * countStates, int * countSymbols)
{
	int numSym;
	int numStates;
	int i;
	int j;
	int k;
	printf("Number of Input Symbols: ");
	scanf(" %d", &numSym);
	printf("Number of States: ", &numSym);
	scanf(" %d", &numStates);
	if ((numSym < 0) || (numStates < 1)) {
		return 1;
	}
	
	//initialize matrix
	*matrix = (int ***) malloc(numStates*sizeof(int **));
	for (i = 0; i < numStates; i++) {
		(*matrix)[i] = (int **) malloc((numSym + 1)*sizeof(int *));
		for (j = 0; j <= numSym; j++) {
			(*matrix)[i][j] = (int *) malloc(numStates*sizeof(int));
			for (k = 0; k < numStates; k++) {
				(*matrix)[i][j][k] = 0;
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
		for (j = 0; j <= numSym; j++) {
			printf("\t");
			getStates((*matrix)[i][j]);
		}
		printf("\n");
	}
	*countStates = numStates;
	*countSymbols = numSym + 1;
	return 0;
}

int getStates(int * array)
{
	int state;
	int num;
	scanf(" %d", &num);
	while (num--) {
		scanf(" %d", &state);
		array[state] = 1;
	}
	return 0;
}
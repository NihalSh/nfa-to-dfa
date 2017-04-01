#include <stdio.h>
#include <stdlib.h>

#define READ_MAX 100

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
	if ((numSym < 1) || (numStates < 1)) {
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
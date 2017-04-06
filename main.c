#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int getStates(int * array);

int getInput(int **** matrix, int * countStates, int * countSymbols);

int e_close(int *** matrix, int numSymbols, int numStates, int * states);

int display(int *** matrix, int numStates, int numSymbols);

int main()
{
	int *** matrix = NULL;
	int numStates;
	int numSymbols;
	int ** dStates = NULL;
	int ** dMatrix = NULL;
	int sizeDFA = 0;
	getInput(&matrix, &numStates, &numSymbols);
	display(matrix, numStates, numSymbols);
	compute(&dStates, &dMatrix, matrix, numStates, numSymbols, &sizeDFA);
	displayDFA(dStates, dMatrix, numStates, numSymbols, sizeDFA);
	return 0;
}
int displayDFA(int ** dStates, int ** dMatrix, int numStates, int numSymbols, int sizeDFA)
{
	int i;
	int j;
	int k;
	int stateId = -1;
	printf("\nDFA\n");

	for (i = 1; i < numSymbols; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	for(i = 0; i < sizeDFA; i++) {
		displayDfaState(dStates[i], numStates);
		for(j = 1; j < numSymbols; j++) {
			printf("\t");
			stateId = dMatrix[i][j];
			displayDfaState(dStates[i], numStates);
		}
		printf("\n");
	}
	return 0;
}

int displayDfaState(int * state, int numStates)
{
	int j;
	printf("{ ");
	for(j = 0; j < numStates; j++) {
		if (state[j] == 1) {
			printf("q%d ", j);
		}
	}
	printf("}");
}

int compute(int *** dStates, int *** dMatrix, int *** matrix, int numStates, int numSymbols, int * sizeDFA)
{
	int j;
	int i = 0;
	int size = 1;
	int * newState = NULL;
	int index = -1;
	//q0 is the start state;

	//initialize a state array
	int * state = NULL;
	initialize_stateArray(&state, numStates);

	//find epsilon closure of the start state
	state[0] = 1;
	e_close(matrix, numSymbols, numStates, state);
	//dStates[0] is just to dereference the pointer, it is not an array
	dStates[0] = (int **) malloc(size * sizeof(int *));
	dStates[0][size - 1] = state;

	while(i < size) {
		for (j = 1; j < numSymbols; j++) {
			initialize_stateArray(&newState, numStates);
			move(matrix, dStates[0][i], j, newState, numStates);
			e_close(matrix, numSymbols, numStates, newState);
			//if newState not in dStates => size++ , push newState to dStates
			dMatrix[0] = (int **) realloc(dMatrix[0], (i + 1) * sizeof(int *));
			dMatrix[0][i] = (int *) malloc(numSymbols * sizeof(int));

			index = locate(*dStates, size, newState, numStates);
			if (index == -1) {
				size++;
				dStates[0] = (int **) realloc(dStates[0], size * sizeof(int *));
				dStates[0][size - 1] = newState;
				index = size - 1;
			}
			dMatrix[0][i][j] = index;
			//dMatrix reallocate and set dMatrix[i][j] = index(newState, dStates)
		}
		i++;
	}
	sizeDFA[0] = size;
	return 0;
}

int locate(int ** dStates, int size, int * state, int numStates)
{
	int i;
	int j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < numStates; j++) {
			if (state[j] != dStates[i][j]) {
				break;
			}
		}
		if (j == numStates) {
			return i;
		}
	}
	return -1;
}
int initialize_stateArray(int ** state, int numStates)
{
	int j;
	state[0] = (int *) malloc(numStates * sizeof(int));
	for (j = 0; j < numStates; j++) {
		state[0][j] = 0;
	}
	return 0;
}

int move(int *** matrix, int * state, int symbol, int * newState, int numStates)
{
	int i;
	int j;
	for (i = 0; i < numStates; i++) {
		if (state[i] == 1) {
			for (j = 0; j < numStates; j++) {
				if (matrix[i][symbol][j] == 1) {
					newState[j] = 1;
				}
			}
		}
	}
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
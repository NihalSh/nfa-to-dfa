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
	printf("Number of Input Symbols: ");
	scanf(" %d", &numSym);
	printf("Number of States: ", &numSym);
	scanf(" %d", &numStates);
	if ((numSym > 26) || (numSym < 1) || (numStates > 26) || (numStates < 1)) {
		return 1;
	}
	printf("\tepsilon");
	for (i = 0; i < numSym; i++) {
		printf("\t%c", 'a' + i);
	}
	printf("\n");
	for (i = 0; i < numStates; i++) {
		printf("%c", 'A' + i);
		for (j = 0; j < numSym; j++) {
			printf("\t");
		}
		printf("\n");
	}
	return 0;
}
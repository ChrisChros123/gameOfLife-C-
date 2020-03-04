// Christina Stiller

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/***********************************************************************************************************************
Game of Life with glider motif.

"*" represents a "living" cell, " " (space) represents a "dead" cell.
Evolution rules:
- iff 3 of its neighbors are alive, a dead cell becomes alive
- if < 2 or > 3 of its neighbors are alive, a iving cell dies
- else, a cell remains unchanged
************************************************************************************************************************/

char**
createField(int size) 
{
	int i;
	char **field = malloc(size * sizeof(char*));
	for (i = 0; i < size; i++) {
		field [i] = malloc(size * sizeof(char));
	}
	return field;
}

/*
Set the starting configuration of the glider.
*/
void
initField(char ** field, int size) 
{
	int m = size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0 ; j< size; j++) {
			if (i >= m-1 && i <= m+1 && j >= m-1 && j <= m+1) {
				field [m-1][m-1] = ' ';
				field [m-1][m] = '*';
				field [m-1][m+1] = ' ';
				field [m][m-1] = ' ';
				field [m][m] = ' ';
				field [m][m+1] = '*';
				field [m+1][m-1] = '*';
				field [m+1][m] = '*';
				field [m+1][m+1] = '*';
				
			} else {
				field [i] [j] = ' ';
			}			
		}
	}
}
/* alternative starting configuration: 
				// pi
				field [m-1][m-1] = '*';
				field [m-1][m] = '*';
				field [m-1][m+1] = '*';
				field [m][m-1] = '*';
				field [m][m] = ' ';
				field [m][m+1] = '*';
				field [m+1][m-1] = '*';
				field [m+1][m] = ' ';
				field [m+1][m+1] = '*';			

*/

void 
printField (char ** field, int size) 
{	

	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%c", field [i] [j]);
		}
		printf("\n");
	}
}

char**
newGeneration (char ** field, int size) 
{
	char** newField = createField(size);
	
	int i, j;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			// counter of alive neighbour cells: 
			int lifeCount = 0; 
			int zeile = i; 
			int spalte = j;

			zeile = ((i-1)% size + size) % size; 
			spalte = ((j-1)% size + size) % size;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
            }
			zeile = ((i-1)% size + size) % size; 
			spalte = ((j+1)% size + size) % size;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}		
			zeile = ((i+1)% size + size) % size;
			spalte = ((j-1)% size + size) % size;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
			zeile = ((i+1)% size + size) % size;
			spalte = ((j+1)% size + size) % size;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
		
			zeile = ((i-1)% size + size) % size;
			spalte = j;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
			zeile = ((i+1)% size + size) % size;
			spalte = j;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
			zeile = i;
			spalte = ((j+1)% size + size) % size;			
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
			zeile = i;
			spalte = ((j-1)% size + size) % size;
			if (field [zeile][spalte] == '*') {
				lifeCount++;
			}
            // check which evolution condition holds
			if (field[i][j] == ' ' && lifeCount == 3 ) { // dead cell with 3 living neighbors
				newField[i][j] = '*';
			}
			else if (field[i][j] == '*' && (lifeCount < 2 || lifeCount > 3)) {
					newField[i][j] = ' '; // dies
			} else {
				newField[i][j] = field[i][j];
			}
		}
	}
	return newField;
}

int 
getArgument (char *arg) {
	int res = 0; 
	int i = 0; 
	char tmp; 
	while (arg[i]) {
		tmp = arg[i];
		if (arg[i]) {
			tmp -= 48;
			res = res *10 + tmp;
		}
		i++;
	}
	return res;	
}


/* 
Starting point of the program.
@param sizeOfField: quadratic size of the field which the glider moves through before it comes out on the other side
@param numberOfGen: number of conformation changes of the glider until the program ends
@param delay: in ms between the conformation changes
*/
int 
main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("3 command line arguments: sizeOfField, numberOfGeneations, delay (in ms) \n");
		return 0;
	}
	int sizeOfField = getArgument(argv[1]);
	if (sizeOfField < 3) {
		printf("sizeOfField must be at least 3.");
		return 0;
	}
	int numberOfGen = getArgument(argv[2]);
	int delay = getArgument(argv[3]);
	char **field = createField(sizeOfField);
	initField(field, sizeOfField);
	printField(field, sizeOfField);
	
	int i; 
	for (i = 0; i < numberOfGen; i++ ) {
		field = newGeneration (field, sizeOfField);
		printField(field, sizeOfField);
		usleep(delay*1000);
	}		
	return 0;
}


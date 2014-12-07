#define NUMTHREADS 11
#define GRIDS 9

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int xCoord[3]={0,3,6};	//Column index at which a subgrid can begin
int yCoord[3]={0,3,6};	//Row index at which a subgrid can begin
int check[NUMTHREADS];

typedef struct {
	int row;
	int column;
	int threadNum;
} parameters;


void *rowValidator(void *argument);
void *columnValidator(void *argument);
void *subgridValidator(void *argument);

//Test Case 1 --Valid
/*
int SudokuArray[9][9]={ {2,4,8,3,9,5,7,1,6},
		        {5,7,1,6,2,8,3,4,9},
		        {9,3,6,7,4,1,5,8,2},
		        {6,8,2,5,3,9,1,7,4},
		        {3,5,9,1,7,4,6,2,8},
		        {7,1,4,8,6,2,9,5,3},
		        {8,6,3,4,1,7,2,9,5},
		        {1,9,5,2,8,6,4,3,7},
		        {4,2,7,9,5,3,8,6,1} };
*/

//Test Case 2 --Valid
/*
int SudokuArray[9][9]={ {1,4,5,3,2,7,6,9,8},
		        {8,3,9,6,5,4,1,2,7},
		        {6,7,2,9,1,8,5,4,3},
		        {4,9,6,1,8,5,3,7,2},
		        {2,1,8,4,7,3,9,5,6},
		        {7,5,3,2,9,6,4,8,1},
		        {3,6,7,5,4,2,8,1,9},
		        {9,8,4,7,6,1,2,3,5},
		        {5,2,1,8,3,9,7,6,4} };
*/

//Test Case 3 --Invalid
/*
int SudokuArray[9][9]={ {1,4,5,3,2,7,6,9,8},
		        {8,3,9,6,5,4,1,2,7},
		        {6,7,2,9,1,8,5,4,3},
		        {4,9,6,1,8,5,3,7,2},
		        {2,1,8,4,7,3,9,5,6},
		        {7,5,3,2,9,6,4,8,1},
		        {3,6,7,5,4,2,1,8,9},	//Swapped the 1 and 8
		        {9,8,4,7,6,1,2,3,5},
		        {5,2,1,8,3,9,7,6,4} };
*/


//Test Case 4 --Valid
/*
int SudokuArray[9][9]={ {5,3,9,2,8,7,1,4,6},
		        {8,1,7,6,3,4,5,9,2},
		        {4,2,6,1,9,5,7,3,8},
		        {7,6,5,3,1,2,9,8,4},
		        {9,4,1,5,6,8,2,7,3},
		        {3,8,2,4,7,9,6,5,1},
		        {1,9,4,7,2,3,8,6,5},
		        {6,5,8,9,4,1,3,2,7},
		        {2,7,3,8,5,6,4,1,9} };
*/

//Test Case 5 --Invalid

int SudokuArray[9][9]={ {3,2,9,6,5,7,8,4,1},
		        {7,4,5,8,3,1,2,9,6},
		        {6,1,8,2,4,9,3,7,5},
		        {1,9,3,4,6,8,5,2,7},
		        {2,7,6,1,9,5,4,9,3},
		        {8,5,4,3,9,1,6,1,9},
		        {4,3,2,7,1,6,9,5,8},
		        {5,8,7,9,2,3,1,6,4},
		        {9,6,1,5,8,4,7,3,2} };



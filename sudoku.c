#include "sudoku.h"

int main(void){

	pthread_t thread_id[NUMTHREADS];
				
	int idIndex = 0;
	int i, k, j;	
	int Correct = 0;

	parameters **data = malloc( NUMTHREADS * sizeof(parameters*) );	//Initialize an array of pointers
	for( i=0; i<NUMTHREADS; i++ )
		data[i] = malloc( sizeof (parameters) );

	idIndex=0; //Index to go through all the thread_id's

	//Generate the threads for all the subGrids.
	for( k=0; k<3; k++ ){
		for( j=0; j<3; j++ ) {
			data[idIndex]->row = yCoord[k]; 
			data[idIndex]->column = xCoord[j];
			data[idIndex]->threadNum = idIndex+1;
			pthread_create(&thread_id[idIndex], NULL, subgridValidator, (void *)data[idIndex]);		
			idIndex++;
		}
	}
	
	//Thread for the columnValidator
	data[idIndex]->row = 0; 
	data[idIndex]->column = 0;
	data[idIndex]->threadNum = idIndex+1;
	pthread_create(&thread_id[idIndex], NULL, columnValidator, (void *)data[idIndex]);
	idIndex++;
	
	//Thread for the rowValidator
	data[idIndex]->row = 0; 
	data[idIndex]->column = 0;
	data[idIndex]->threadNum = idIndex+1;
	pthread_create(&thread_id[idIndex], NULL, rowValidator, (void *)data[idIndex]);

	for(i=0;i<NUMTHREADS;i++){
		pthread_join(thread_id[i],NULL);	//Join all the threads
		Correct=Correct+check[i];		//Count the value of all the checks.
	}

	if( Correct == NUMTHREADS )	//Check to see if all the threads provided a check value of 1.
		printf("~Provided sudoku is a valid solution~\n");
	else
		printf("~Provided sudoku is not a valid solution~\n"); 

	//Free all the allocated memory
	for(i=0;i<NUMTHREADS;i++)
		free(data[i]);	
	free(data);

	return 0;
}

//This thread checks to see that all the columns in the Sudoku Solution contain the numbers 1-9.
void  *columnValidator(void *argument){

	parameters *args= (parameters *) argument;
	int k,i,j;
	int countInner=0;
	int countColumn=0;
	int threadNum;

	threadNum = args->threadNum;

	for( k=0; k<9; k++ ){ 	//Iterate through the 9 columns
		countInner=0;
		for( i=1; i<=9; i++ ){	//Look for the number i in the kth column	
			for( j=0; j<9; j++ ){	// Iterate through the kth column 
				if( SudokuArray[j][k]==i ){
					countInner++;	//Increase count everytime it finds a value in the column
					break;		//Break out of loop and look for next number
				}
			}
		}
		if( countInner==9 ) //If it found all the numbers in the kth column increase the countColumn
			countColumn++;
	}

	if( countColumn==9 )
		check[threadNum-1]=1;
	else
		check[threadNum-1]=0;
	
	pthread_exit(NULL);
	
}

//This thread checks to see that all the rows in the Sudoku Solution contain the numbers 1-9.
void *rowValidator(void* argument){
	parameters *args= (parameters *) argument;	
	int k,i,j;	
	int countInner=0;
	int countRow=0;
	int threadNum;

	threadNum = args->threadNum;

	for( k=0; k<9; k++ ){ //Iterate through the 9 rows
		countInner=0;
		for( i=1; i<=9; i++ ){	//Look for the number i in the kth row (iterate through the columns)		
			for( j=0; j<9; j++ ){	//Iterate through the kth row.
				if( SudokuArray[k][j]==i ){
					countInner++;	//Increase count everytime it finds a value in the row
					break;		//Break out of loop and look for next number
				}
			}
		}
		if( countInner==9 ) //If it found all the numbers in the kth row increase the countRow
			countRow++;
	}

	if( countRow ==9 )
		check[threadNum-1]=1;
	else
		check[threadNum-1]=0;

	pthread_exit(NULL);

}

//This tread checks to see if a given subgrid of the Sudoku solution contain the numbers 1-9
void *subgridValidator(void * argument){
	parameters *args= (parameters *) argument;	
	int row,col,threadNum;
	int row3,col3;
	int i=0;
	int count=0;	
	
	col = args->column; //Column index of where to begin checking subgrid
	row = args->row;    //Row index of where to begin checking subgrid
	threadNum = args->threadNum;

	for( i=1; i<=9; i++ ){	//Iterate through the numbers 1-9
		for( row3=0; row3<3; row3++){	//Iterate through the rows of the subgrid
			for( col3=0; col3<3; col3++ ){	//Iterate through the columns of the subgrid
				//Look for the number i in the subgrid also check to see that 
				//the next count value would be the next number we are looking for (i).
				if( SudokuArray[row3+row][col3+col] == i && (count+1)==i )
					count++;
			}
		}
	}

	if( count==9 )
		check[threadNum-1]=1;
	else
		check[threadNum-1]=0;

	pthread_exit(NULL);

}


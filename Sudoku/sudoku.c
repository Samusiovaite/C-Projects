//Kamile Samusiovaite - 2ND, SUDOKU 
#include <stdio.h>
#include <stdlib.h>

#define N 9

//Function prototypes
void print(int sudoku[N][N]);
int isSuitablePlace(int sudoku[N][N], int row, int column, int num);
int solveSudoku(int sudoku[N][N], int row, int column);

int main(){
	//0 means empty space  
	int sudoku[N][N] = {{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
					{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
					{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
					{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
					{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
					{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
					{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
					{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
					{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }};

	if(solveSudoku(sudoku, 0, 0) == 1){
		print(sudoku);
	}
	else{
		printf("No sudoku solution exists");
	}
		
	return 0;
}

//printing function
void print(int sudoku[N][N]){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d ",sudoku[i][j]);
			
		}
		printf("\n");
	}
}

//checks whether a number can be assigned to a specified row, column, matrix
int isSuitablePlace(int sudoku[N][N], int row, int column, int num){
	
	//check that the same number is in the same column
	for (int i = 0; i < 9; ++i){
		if (sudoku[i][column] == num){
			return 0;
		}
	}
	
	//check that the same number is in the same row 
	for (int i = 0; i < 9; ++i){
		if (sudoku[row][i] == num){
			return 0;
		}	
	}
	
	//Check if we find the same num in the particular 3*3 matrix
	int startRow = row - row % 3;
	int startColumn = column - column % 3;

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			if (sudoku[startRow + i][startColumn + j] == num){
				return 0;
			}
		}	
		return 1;
	}
}

//trying to complete sudoku by assign values 
int solveSudoku(int sudoku[N][N], int row, int column){
	
	//when program reach row 8 and column 9 no longer allow to go back
	if (row == N - 1 && column == N){
		return 1;
	}
	
	//when the ninth column is reached moves to the next row 
	if (column == N){ 
		row++; 
		column = 0;
	}
	
	//checking that the value is not 0, moves to the next number 
	if (sudoku[row][column] > 0){
		return solveSudoku(sudoku, row, column + 1);
	}
		
	for (int num = 1; num <= N; num++){
		
		//checks if a number can be placed in a specific location
		if (isSuitablePlace(sudoku, row, column, num) == 1){
			
			//a number is assigned and it is assumed to be correct 
			sudoku[row][column] = num;
		
			// Checking for next possibility with next column
			if (solveSudoku(sudoku, row, 1 + column ) == 1)
				return 1;
		}

		/*the assigned number is removed because the assumption was incorrect,
		moving on to another assumption with a different numerical value*/
		sudoku[row][column] = 0;
	}
	return 0;
}


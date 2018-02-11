/*
*	ANKUR DUBEY
*	PROJECT INVOLVING FILE HANDLING:SUDOKU SOLVER
*/

/*
*	SUDOKUMATRIX.H
*		PROVIDES CLASS DECLARATIONS FOR THE CLASS "SudokuMatrix"
*	a)Code follows the ISO C++ 11 standard
*	b)Compile using -std=c++11 or -std=gnu++11
*/

#include <fstream>
#include <iostream>

//Supporting Structures
struct rawMatrix {
	//Structure for incoming data 
	int serialNum;
	int matrix[9][9];
};
struct matrixCoordinate {
	//Ordered pair of coordinates of square matrix
	int i, j;
};

class SudokuMatrix {
	/*
	 *	Assumes sudoku to be a generic 9x9 type
	 *
	 *  Private Data Members:
	 *	_mainMatrix: 	  Sudoku is read to this matrix.All operations and changes are directly done to this matrix
	 *	_subMatrix: 	  Array of 2D matrices containing individual sudoku 3x3 blocks
	 *	_transposeMatrix: Transpose of _mainMatrix
	 *	_originalMatrix:  Original Copy of Sudoku Problem
	 *  _vacantPositions: Stores data related to empty positions
	 *	_isSolvable:	  Value is set to 1 if unique solution exists else -1
	 *	_problemNo:		  Sr. No. to be taken from input file
	 *
	 *	Private Methods:
	 *	_generateBlockMatrix():     Breaks _mainMatrix into subblocks
	 *	_nextOf():					Returns address of next element
	 *	_generateVacantPositions(): Populates _vacantPositions
	 *  _validity(): 			    Returns 1 if no illegal entries are found
	 *	_rowValidity():				Checks if a certain row is valid
	 *	_coloumnValidity():			Checks if a certain coloumn is valid
	 *	_blockValidity():			Checks if a certain block is valid
	 *	_solve():					Solves the sudoku problem using a brute force algorithm
	 *	_status():					Returns 1 if the sudoku has been solved,0 if not solved and -1 condition for
	 *								non-solvability is achieved
	 *
	 *	Public Methods:
	 *	initialize():				Calls all functions upto _solve(), ACTS AS CONSTRUCTOR
	 *	exportFile():				Stores(append) the solution to a text file
	 *	displaySolution:			Dsiplays solution on screen
	 *	problemNo():				Returns _problemNo
	 */

private:
	//Private Data Members
	int _mainMatrix[9][9], _subMatrix[9][3][3], _transposeMatrix[9][9], _originalMatrix[9][9];
	int _isSolvable, _problemNo;
	struct vacantEntries {
		int numofEntries;
		matrixCoordinate coordinate[81];
	}_vacantPositions;

	//Private Methods
	void _generateBlockMatrix();
	void _generateVacantPositions();
	matrixCoordinate _nextOf(matrixCoordinate current, int max);
	int _rowValidity(int n);
	int _coloumnValidity(int n);
	int _blockValidity(int n);
	int _validity();
	void _solve();
	int _status();

public:
	//Public Methods
	void exportFile(char path[]);
	void initialize(rawMatrix raw);
	void displaySolution();
	int problemNo();
};
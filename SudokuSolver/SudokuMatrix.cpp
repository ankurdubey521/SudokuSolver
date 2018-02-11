/*
*	ANKUR DUBEY
*	PROJECT INVOLVING FILE HANDLING:SUDOKU SOLVER
*/

/*
*	SUDOKUMATRIX.CPP
*	PROVIDES METHOD DEFINITIONS FOR THE CLASS "SudokuMatrix"
*	a)Code follows the ISO C++ 11 standard
*	b)Compile using -std=c++11 or -std=gnu++11
*/

#include <fstream>
#include <iostream>
#include "SudokuMatrix.h"

//Private Methods
void SudokuMatrix::_generateBlockMatrix() {
	/*
	*	Breaks _mainMatrix into 9 subblocks and stores in _subMatrix
	*	First index of _subMatrix indicates block number.
	*	Block Numbers are assigned in sequential fashion from 0->8
	*/

	//Block 0-2
	for (int n = 0; n < 3; ++n) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				_subMatrix[n][i][j] = _mainMatrix[i][j + (n * 3)];
			}
		}
	}
	//Block 3-5
	for (int n = 3; n < 6; ++n) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				_subMatrix[n][i][j] = _mainMatrix[i + 3][j + ((n - 3) * 3)];
			}
		}
	}
	//Block 6-8
	for (int n = 6; n < 9; ++n) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				_subMatrix[n][i][j] = _mainMatrix[i + 6][j + ((n - 6) * 3)];
			}
		}
	}
}
matrixCoordinate SudokuMatrix::_nextOf(matrixCoordinate current, int max) {
	/*
	*	Returns the coordinate of the cell adjacent to current
	*	Exclusively used for loop iteration
	*/
	matrixCoordinate next;
	if (current.j == max) {
		next = { (current.i) + 1,0 };
	}
	else {
		next = { current.i,(current.j) + 1 };
	}
	return next;
}
int SudokuMatrix::_rowValidity(int n) {
	/*
	*	Checks if a certain row is valid
	*	Note:there can be multiple 0 as 0 signifies blank entry
	*/
	for (int i = 0; i < 9; ++i) {
		for (int j = i + 1; j < 9; ++j) {
			if (_mainMatrix[n][i] != 0) {
				if (_mainMatrix[n][i] == _mainMatrix[n][j]) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int SudokuMatrix::_coloumnValidity(int n) {
	/*
	*	Checks if a certain coloumn is valid
	*	Note:there can be multiple 0 as 0 signifies blank entry
	*/
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			_transposeMatrix[i][j] = _mainMatrix[j][i];
		}
	}
	for (int i = 0; i < 9; ++i) {
		for (int j = i + 1; j < 9; ++j) {
			if (_transposeMatrix[n][i] != 0) {
				if (_transposeMatrix[n][i] == _transposeMatrix[n][j]) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int SudokuMatrix::_blockValidity(int n) {
	/*
	*	Checks if a certain block is valid
	*	Note:there can be multiple 0 as 0 signifies blank entry
	*/
	for (matrixCoordinate a = { 0,0 }; a.i != 3; a = _nextOf(a, 2)) {
		for (matrixCoordinate b = _nextOf(a, 2); b.i != 3; b = _nextOf(b, 2)) {
			if (_subMatrix[n][a.i][a.j] != 0) {
				if (_subMatrix[n][a.i][a.j] == _subMatrix[n][b.i][b.j]) {
					return 0;
				}
			}
		}
	}
	return 1;
}
int SudokuMatrix::_validity() {
	/*
	*	Returns 1 if there are no illegal entries else returns 0
	*	Note:there can be multiple 0 as 0 signifies blank entry
	*/
	_generateBlockMatrix();
	//	Actually running the validity checks
	for (int i = 0; i < 9; ++i) {
		if (_rowValidity(i) == 0 || _coloumnValidity(i) == 0 || _blockValidity(i) == 0) {
			return 0;
		}
	}
	return 1;
}
void SudokuMatrix::_generateVacantPositions() {
	/*
	*	Populates _vacantPositions
	*	_vacantPositions.coordinate store coordinates of vacant positions
	*/
	_vacantPositions.numofEntries = 0;
	matrixCoordinate last = { 8,8 };
	for (matrixCoordinate a = { 0,0 }; a.i != 9; a = _nextOf(a, 8)) {
		if (_mainMatrix[a.i][a.j] == 0) {
			_vacantPositions.coordinate[_vacantPositions.numofEntries++] = a;
		}
	}
}
int SudokuMatrix::_status() {
	//Returns 1 if the sudoku has been solved,0 if not solved
	int flag = 0;
	for (int a = 0; a < _vacantPositions.numofEntries; ++a) {
		if (_mainMatrix[_vacantPositions.coordinate[a].i][_vacantPositions.coordinate[a].j] == 0) {
			flag = 1;
		}
	}
	if (_validity() && flag == 0) {
		return 1;
	}
	return 0;
}
void SudokuMatrix::_solve() {
	//Solves the sudoku provided there exists a unique solution to it
	int currentVacancyPos = 0;
	while (!_status()) {
		if (_mainMatrix[_vacantPositions.coordinate[currentVacancyPos].i][_vacantPositions.coordinate[currentVacancyPos].j] == 9) {
			_mainMatrix[_vacantPositions.coordinate[currentVacancyPos].i][_vacantPositions.coordinate[currentVacancyPos].j] = 0;
			currentVacancyPos--;
			continue;
		}
		else {
			_mainMatrix[_vacantPositions.coordinate[currentVacancyPos].i][_vacantPositions.coordinate[currentVacancyPos].j]++;
		}
		if (_validity() == 1) {
			currentVacancyPos++;
		}
		else if (_validity() == 0) {
			if (_mainMatrix[_vacantPositions.coordinate[currentVacancyPos].i][_vacantPositions.coordinate[currentVacancyPos].j] == 9) {
				_mainMatrix[_vacantPositions.coordinate[currentVacancyPos].i][_vacantPositions.coordinate[currentVacancyPos].j] = 0;
				currentVacancyPos--;
			}
		}
		else if (_validity() == -1) {
			_isSolvable = 0;
		}
	}
	if (_isSolvable != 0) {
		_isSolvable = 1;
	}
}

//Public Methods
void SudokuMatrix::initialize(rawMatrix raw) {
	//Populate _mainMatrix,_originalMatrix,_transposeMatrix
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			_mainMatrix[i][j] = raw.matrix[i][j];
			_originalMatrix[i][j] = _mainMatrix[i][j];
			_transposeMatrix[j][i] = _mainMatrix[i][j];
		}
	}
	//Populate _problemNo
	_problemNo = raw.serialNum;
	//Populate _vacantPositions
	_generateVacantPositions();
	//Solve the sudoku
	_solve();
}
void SudokuMatrix::exportFile(char path[]) {
	/*
	*	Stores(appends) the solution to a text file
	*/
	std::fstream outputFile(path, std::ios::out | std::ios::app);
	outputFile.seekp(std::ios::end);
	if (outputFile.is_open()) {
		outputFile << "\n#" << _problemNo << std::endl;
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0) {
				outputFile << ' ';
				for (int k = 1; k <= 19; ++k) {
					outputFile << '-';
				}
				outputFile << std::endl;
			}
			for (int j = 0; j < 9; ++j) {
				if (j % 3 == 0) {
					outputFile << " | ";
				}
				outputFile << _mainMatrix[i][j];
			}
			outputFile << " |" << std::endl;
		}
		outputFile << ' ';
		for (int i = 1; i <= 19; ++i) {
			outputFile << '-';
		}
		outputFile << std::endl;
	}
	outputFile.close();
}
void SudokuMatrix::displaySolution() {
	/*
	*	Displays the solution on screen
	*/
	std::cout << "\n#" << _problemNo << std::endl;
	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			std::cout << ' ';
			for (int k = 1; k <= 19; ++k) {
				std::cout << '-';
			}
			std::cout << std::endl;
		}
		for (int j = 0; j < 9; ++j) {
			if (j % 3 == 0) {
				std::cout << " | ";
			}
			std::cout << _mainMatrix[i][j];
		}
		std::cout << " |" << std::endl;
	}
	std::cout << ' ';
	for (int i = 1; i <= 19; ++i) {
		std::cout << '-';
	}
	std::cout << std::endl;
}
int SudokuMatrix::problemNo() {
	return _problemNo;
}
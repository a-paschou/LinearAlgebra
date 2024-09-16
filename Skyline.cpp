#include "Skyline.h"
#include <stdexcept>
#include <iostream>

Skyline::Skyline(int numOfRows, int numOfCols, std::vector<double>* values)
	//: numOfRows{ static_cast<const unsigned int>(numOfRows) }, numOfCols{ static_cast<const unsigned int>(numOfCols) }
{
	if (values->size() != (numOfRows * numOfCols))
	{
		throw std::invalid_argument("The dimensions and the number of values of the matrix do not match.");
	}
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	diagOfSets = new std::vector<int>();
	this->values = new std::vector<double>();
	heights = new std::vector<int>();

	isSymmetric = true;
	CheckSymmetry(numOfRows, numOfCols, values);

	if (isSymmetric)
	{
		StoreSymmetricValues(values);
	}
	else
	{
		StoreNonSymmetricValues(values);
	}

}

double Skyline::FindValue(int row, int col)
{
	if (isSymmetric)
	{
		return ReturnValueFromSymmetricMatrix(row, col);
	}
	else
	{
		return ReturnValueFromNonSymmetricMatrix(row, col);
	}
	
}

Matrix* Skyline::MatrixByMatrixMultiplication(Matrix& rightMatrix)
{
	if (numOfCols != rightMatrix.numOfRows)
	{
		throw std::invalid_argument("The dimensions of the matrices do not match.");
	}
	std::vector<double>* newValues = new std::vector<double>();
	for (size_t i = 0; i < this->numOfRows; i++)
	{
		for (size_t j = 0; j < rightMatrix.numOfCols; j++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < this->numOfCols; k++)
			{
				sum += this->FindValue(i, k) * rightMatrix.FindValue(k, j);
			}
			newValues->push_back(sum);
		}
	}
	Matrix* newMatrix = new Skyline(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* Skyline::MatrixAddition(Matrix& rightMatrix)
{
	if (numOfRows != rightMatrix.numOfRows || numOfCols != rightMatrix.numOfCols)
	{
		throw std::invalid_argument("The dimensions of the matrices do not match.");
	}
	std::vector<double>* newValues = new std::vector<double>();
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			newValues->push_back(this->FindValue(i, j) + rightMatrix.FindValue(i, j));
		}
	}
	Matrix* newMatrix = new Skyline(numOfRows, numOfCols, newValues);
}

void Skyline::StoreSymmetricValues(std::vector<double>* values)
{
	//diagOfSets->push_back(0);
	int row{ 0 };
	int temporarySet{ 0 };
	for (int j = 0; j < numOfCols; j++)
	{
		temporarySet += j - row;
		diagOfSets->push_back(temporarySet);
		row = 0;
		bool answer{ true };
		//int row{ 0 };
		do
		{
			if ((values->at(row * numOfCols + j) == 0))
			{
				row += 1;
			}
			else
			{
				answer = false;
			}
		} while (answer && (row != j));
	}
	temporarySet += numOfCols - row;
	diagOfSets->push_back(temporarySet);

	for (size_t i = 0; i < (diagOfSets->size() - 1); i++)
	{
		heights->push_back(diagOfSets->at(i + 1) - diagOfSets->at(i) - 1);
	}

	for (int j = 0; j < heights->size(); j++)
	{
		int row{ j };
		while (j - row <= heights->at(j))
		{
			this->values->push_back(values->at(row * numOfCols + j));
			row--;
		}
	}
}

void Skyline::StoreNonSymmetricValues(std::vector<double>* values)
{
	StoreSymmetricValues(values);

	//diagOfSets->push_back(0);
	int col{ 0 };
	int temporarySet{ 0 };
	for (int i = 0; i < numOfRows; i++)
	{
		temporarySet += i - col;
		diagOfSets->push_back(temporarySet);
		col = 0;
		bool answer{ true };
		//int col{ 0 };
		do
		{
			if ((values->at(i * numOfCols + col) == 0))
			{
				col += 1;
			}
			else
			{
				answer = false;
			}
		} while (answer && (col != i));
	}
	temporarySet += numOfRows - col;
	diagOfSets->push_back(temporarySet);

	for (size_t i = (numOfCols + 1); i < (diagOfSets->size() - 1); i++)
	{
		heights->push_back(diagOfSets->at(i + 1) - diagOfSets->at(i) - 1);
	}

	for (int i = numOfCols; i < heights->size(); i++)
	{
		int col{ i };
		while (i - col <= heights->at(i))
		{
			this->values->push_back(values->at((i - numOfCols)*numOfCols + (col - numOfCols)));
			col--;
		}
	}
}

double Skyline::ReturnValueFromSymmetricMatrix(int row, int col)
{
	if ((row < 0) || (col < 0) || (row >= numOfRows) || (col >= numOfCols))
	{
		throw std::invalid_argument("The given dimension indices are not correct.");
	}
	if (row > col)
	{
		row += col;
		col = row - col;
		row -= col;
	}
	if (col - row <= heights->at(col))
	{
		return this->values->at(diagOfSets->at(col) + col - row);;
	}
	else
	{
		return 0.0;
	}
}

double Skyline::ReturnValueFromNonSymmetricMatrix(int row, int col)
{
	if (row <= col)
	{
		return ReturnValueFromSymmetricMatrix(row, col);
	}
	else
	{
		if (row - col <= heights->at(row + numOfCols))
		{
			return this->values->at(diagOfSets->at(numOfCols + row + 1) + diagOfSets->at(numOfCols) + row - col);
		}
		else
		{
			return 0.0;
		}
	}
}

Matrix* Skyline::Transpose()
{
	if (this->isSymmetric)
	{
		return this;
	}
	else
	{
		std::vector<double>* transposedValues = nullptr;
		for (size_t j = 0; j < numOfCols; j++)
		{
			for (size_t i = 0; i < numOfRows; i++)
			{
				transposedValues->push_back(FindValue(i, j));
			}
		}
		Matrix* newMatrix = new Skyline(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

Skyline::~Skyline()
{
	std::cout << "Calling Destructor" << std::endl;
}

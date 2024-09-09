#include "PackedStorageFormat.h"
#include <iostream>
#include <stdexcept>
#include "FullStorageFormat.h"

PackedStorageFormat::PackedStorageFormat(int numOfRows, int numOfCols, std::vector<double>* values)
	//:numOfRows{ numOfRows }, numOfCols{ numOfCols }, values {nullptr}
{
	if (numOfCols != numOfRows)
	{
		throw std::invalid_argument("The given dimensions do not correspond to a square matrix.");
	}
	else if (values->size() != (numOfRows * numOfCols))
	{
		throw std::invalid_argument("The dimensions and the number of values of the matrix do not match.");
	}
	CheckSymmetry(numOfRows, numOfCols, values);
	if (!isSymmetric)
	{
		throw std::invalid_argument("The matrix is not symmetric.");
	}
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	this->values = new std::vector<double>();
	int count{ 0 };
	for (size_t i = 0; i <= numOfRows; i++)
	{
		for (size_t j = i; j < numOfCols; j++)
		{
			this->values->push_back(values->at(i * numOfCols + j));
			count++;
		}
	}
}

double PackedStorageFormat::FindValue(int row, int col)
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
	return values->at(col + (2 * numOfCols - row - 1) * row / 2);
}

Matrix* PackedStorageFormat::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
	FullStorageFormat* newMatrix = new FullStorageFormat(numOfCols, this->numOfRows, newValues);
	return newMatrix;
}

Matrix* PackedStorageFormat::MatrixAddition(Matrix& rightMatrix)
{
	if (numOfCols != rightMatrix.numOfRows)
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
	FullStorageFormat* newMatrix = new FullStorageFormat(numOfRows, numOfCols, newValues);
	return newMatrix;
}

Matrix* PackedStorageFormat::Transpose()
{
	return this;
}

PackedStorageFormat::~PackedStorageFormat()
{
	std::cout << "Calling Destructor" << std::endl;
}

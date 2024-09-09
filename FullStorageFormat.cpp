#include "FullStorageFormat.h"
#include <stdexcept>
#include <iostream>

FullStorageFormat::FullStorageFormat(const int numOfRows,const int numOfCols,std::vector<double>* values)
	/* :numOfRows{ numOfRows }, numOfCols{ numOfCols }, values{ values }*/
{

	if ((numOfRows * numOfCols) != values->size())
	{
		throw std::invalid_argument("The dimensions and the number of values of the matrix do not match.");
	}
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	this->values = values;
	CheckSymmetry(numOfRows, numOfCols, values);
}

double FullStorageFormat::FindValue(int row, int col)
{
	if ((row < 0) || (col < 0) || (row >= numOfRows) || (col >= numOfCols))
	{
		throw std::invalid_argument("The given dimension indices are not correct.");
	}
	return values->at(row * numOfCols + col);
}

Matrix* FullStorageFormat::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
			double sum{0};
			for (size_t k = 0; k < this->numOfCols; k++)
			{
				sum += this->FindValue(i, k) * rightMatrix.FindValue(k, j);
			}
			newValues->push_back(sum);
		}
	}
	Matrix* newMatrix = new FullStorageFormat(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* FullStorageFormat::MatrixAddition(Matrix& rightMatrix)
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
	Matrix* newMatrix = new FullStorageFormat(numOfRows, numOfCols, newValues);
	return newMatrix;
}

Matrix* FullStorageFormat::Transpose()
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
		Matrix* newMatrix = new FullStorageFormat(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

FullStorageFormat::~FullStorageFormat()
{
	std::cout << "Calling Destructor" << std::endl;
}

#include "CoordinateList.h"
#include <stdexcept>
#include <iostream>

CoordinateList::CoordinateList(int numOfRows, int numOfCols, std::vector<double>* values)
	//:numOfRows{ numOfRows }, numOfCols{ numOfCols }, rows { nullptr }, cols{ nullptr }, values{ nullptr }
{
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	this->rows = new std::vector<int>();
	this->cols = new std::vector<int>();
	this->values = new std::vector<double>();

	CheckSymmetry(numOfRows, numOfCols, values);
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			if (values->at(i * numOfCols + j) != 0)
			{
				this->values->push_back(values->at(i * numOfCols + j));
				this->rows->push_back(i);
				this->cols->push_back(j);
			}
		}
	}
}

double CoordinateList::FindValue(int row, int col)
{
	if ((row < 0) || (col < 0) || (row >= numOfRows) || (col >= numOfCols))
	{
		throw std::invalid_argument("The given dimension indices are not correct.");
	}
	for (size_t i = 0; i < rows->size(); i++)
	{
		if ((rows->at(i) == row) &&  (cols->at(i) == col))
		{
			return values->at(i);
		}
	}
	return 0.0;
}

Matrix* CoordinateList::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
	CoordinateList* newMatrix = new CoordinateList(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* CoordinateList::MatrixAddition(Matrix& rightMatrix)
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
	CoordinateList* newMatrix = new CoordinateList(numOfRows, rightMatrix.numOfCols, newValues);
}

Matrix* CoordinateList::Transpose()
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
		Matrix* newMatrix = new CoordinateList(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

CoordinateList::~CoordinateList()
{
	std::cout << "Calling Destructor" << std::endl;
	delete rows;
	delete cols;
	delete values;
}

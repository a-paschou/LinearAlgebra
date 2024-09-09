#include "DiagonalMatrix.h"
#include <stdexcept>
#include "CompressedSparseRows.h"

DiagonalMatrix::DiagonalMatrix(int numOfRows, int numOfCols, std::vector<double>* values)
{
	if (values->size() != (numOfRows * numOfCols))
	{
		throw std::invalid_argument("The dimensions and the number of values of the matrix do not match.");
	}
	this->values = new std::vector<double>();
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	for (size_t i = 0; i < this->numOfRows; i++)
	{
		this->values->push_back(values->at(i * numOfCols + i));
	}
}

double DiagonalMatrix::FindValue(int row, int col)
{
	if (row == col)
	{
		return values->at(row);
	}
	return 0.0;
}

Matrix* DiagonalMatrix::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
			double sum{ this->FindValue(i, i) * rightMatrix.FindValue(i, j) };
			newValues->push_back(sum);
		}
	}
	Matrix* newMatrix = new CompressedSparseRows(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* DiagonalMatrix::MatrixAddition(Matrix& rightMatrix)
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
	Matrix* newMatrix = new CompressedSparseRows(numOfRows, numOfCols, newValues);
}

Matrix* DiagonalMatrix::Transpose()
{
	return this;
}

DiagonalMatrix::~DiagonalMatrix()
{
}

#include "CompressedSparseRows.h"
#include <stdexcept>
#include <iostream>

CompressedSparseRows::CompressedSparseRows(int numOfRows, int numOfCols, std::vector<double>* values)
	//:numOfRows{ numOfRows }, numOfCols{ numOfCols }, rowOffsets{ nullptr }, colIndices{ nullptr }, values{ nullptr }
{
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	rowOffsets = new std::vector<int>();
	colIndices = new std::vector<int>();
	this->values = new std::vector<double>();

	CheckSymmetry(numOfRows, numOfCols, values);
	int countSets{ 0 };
	rowOffsets->push_back(0);
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			if (values->at(i * numOfCols + j) != 0)
			{
				this->values->push_back(values->at(i * numOfCols + j));
				this->colIndices->push_back(j);
				countSets++;
			}
		}
		rowOffsets->push_back(countSets);
	}
}

double CompressedSparseRows::FindValue(int row, int col)
{
	if ((row < 0) || (col < 0) || (row >= numOfRows) || (col >= numOfCols))
	{
		throw std::invalid_argument("The given dimension indices are not correct.");
	}
	for (size_t i = rowOffsets->at(row); i < rowOffsets->at(row + 1); i++)
	{
		if (colIndices->at(i) == col)
		{
			return values->at(i);
		}
	}
	return 0.0;
}

Matrix* CompressedSparseRows::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
	CompressedSparseRows* newMatrix = new CompressedSparseRows(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* CompressedSparseRows::MatrixAddition(Matrix& rightMatrix)
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
	CompressedSparseRows* newMatrix = new CompressedSparseRows(numOfRows, numOfCols, newValues);
}

Matrix* CompressedSparseRows::Transpose()
{
	if (this->isSymmetric)
	{
		return this;
	}
	else
	{
		std::vector<double>* transposedValues = new std::vector<double>();
		for (size_t j = 0; j < numOfCols; j++)
		{
			for (size_t i = 0; i < numOfRows; i++)
			{
				transposedValues->push_back(FindValue(i, j));
			}
		}
		Matrix* newMatrix = new CompressedSparseRows(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

CompressedSparseRows::~CompressedSparseRows()
{
	std::cout << "Calling Destructor" << std::endl;
	delete values;
	delete rowOffsets;
	delete colIndices;
}

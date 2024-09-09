#include "CompressedSparseColumns.h"
#include <stdexcept>
#include <iostream>

CompressedSparseColumns::CompressedSparseColumns(int numOfRows, int numOfCols, std::vector<double>* values)
	//: numOfRows{ numOfRows }, numOfCols{ numOfCols }, rowIndices{ nullptr }, colOffsets{ nullptr }, values {nullptr}
{
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	rowIndices = new std::vector<int>();
	colOffsets = new std::vector<int>();
	this->values = new std::vector<double>();

	CheckSymmetry(numOfRows, numOfCols, values);
	int countSets = 0;
	colOffsets->push_back(countSets);
	for (size_t j = 0; j < numOfCols; j++)
	{
		for (size_t i = 0; i < numOfRows; i++)
		{
			if (values->at(i * numOfCols + j) != 0)
			{
				this->values->push_back(values->at(i * numOfCols + j));
				rowIndices->push_back(i);
				countSets++;
			}
		}
		colOffsets->push_back(countSets);
	}

}

double CompressedSparseColumns::FindValue(int row, int col)
{
	if ((row < 0) || (col < 0) || (row >= numOfRows) || (col >= numOfCols))
	{
		throw std::invalid_argument("The given dimension indices are not correct.");
	}
	for (size_t i = colOffsets->at(col); i < colOffsets->at(col + 1); i++)
	{
		if (rowIndices->at(i) == row)
		{
			return values->at(i);
		}
	}
	return 0.0;
}

Matrix* CompressedSparseColumns::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
	CompressedSparseColumns* newMatrix = new CompressedSparseColumns(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* CompressedSparseColumns::MatrixAddition(Matrix& rightMatrix)
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
	CompressedSparseColumns* newMatrix = new CompressedSparseColumns(numOfRows, numOfCols, newValues);
}

Matrix* CompressedSparseColumns::Transpose()
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
		Matrix* newMatrix = new CompressedSparseColumns(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

CompressedSparseColumns::~CompressedSparseColumns()
{
	std::cout << "Calling Destructor" << std::endl;
}

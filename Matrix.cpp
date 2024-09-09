#include "Matrix.h"
#include <iostream>

Matrix::Matrix()
{
}

double Matrix::FindValue(int, int)
{
	return 0.0;
}

Matrix* Matrix::MatrixByMatrixMultiplication(Matrix&)
{
	return nullptr;
}

Matrix* Matrix::MatrixAddition(Matrix&)
{
	return nullptr;
}

void Matrix::CheckSymmetry(int numOfRows, int numOfCols, std::vector<double>* values)
{
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			double maxAbsValue{ std::max(std::abs(values->at(i * numOfCols + j)), std::abs(values->at(j * numOfCols + i))) };
			double minAbsValue{ std::min(std::abs(values->at(i * numOfCols + j)), std::abs(values->at(j * numOfCols + i))) };
			double error{ maxAbsValue / minAbsValue };
			if (error > 1.00000001)
			{
				isSymmetric = false;
				break;
			}
		}
	}
}

void Matrix::PrintMatrix()
{
	for (size_t i = 0; i < this->numOfRows; i++)
	{
		for (size_t j = 0; j < this->numOfCols; j++)
		{
			std::cout << this->FindValue(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

Matrix* Matrix::Transpose()
{
	return nullptr;
}

Matrix::~Matrix()
{
}

int* Matrix::GetMatrixDimensions()
{
	int* dimensions = new int[2] {numOfRows, numOfCols};
	return dimensions;
}

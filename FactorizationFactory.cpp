#include "FactorizationFactory.h"
#include <iostream>
#include "CompressedSparseRows.h"
#include "DiagonalMatrix.h"

FactorizationFactory::FactorizationFactory(Matrix* matrix, FactorizationType type)
{
	switch (type)
	{
	case FactorizationType::LU:
		LUFactorization(matrix);
		break;
	case FactorizationType::LDU:
		LDUFactorization(matrix);
		break;
	case FactorizationType::Cholesky:
		CholeskyFactorization(matrix);
		break;
	case FactorizationType::LDL:
		LDLFactorization(matrix);
		break;
	default:
		break;
	}
}

void FactorizationFactory::LUFactorization(Matrix* matrix)
{
	int* dimensions {matrix->GetMatrixDimensions()};
	std::vector<double>* lowerTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	std::vector<double>* upperTriangle = new std::vector<double>();
	for (size_t i = 0; i < dimensions[0]; i++)
	{
		for (size_t j = 0; j < dimensions[1]; j++)
		{
			upperTriangle->push_back(matrix->FindValue(i, j));
		}
	}
	for (size_t i = 0; i < dimensions[0] - 1; i++)
	{
		for (size_t j = i + 1; j < dimensions[0]; j++)
		{
			double newValue{ upperTriangle->at(j*dimensions[1] + i) / upperTriangle->at(i * dimensions[1] + i) };
			lowerTriangle->at(j * dimensions[1] + i) = newValue;

			for (size_t k = i; k < dimensions[0]; k++)
			{
				newValue = upperTriangle->at(j * dimensions[1] + k) - lowerTriangle->at((j * dimensions[1] + i)) * upperTriangle->at(i * dimensions[1] + k);
				upperTriangle->at(j * dimensions[1] + k) = newValue;
			}
		}
	}
	for (size_t i = 0; i < dimensions[0]; i++)
	{
		lowerTriangle->at(i * dimensions[1] + i) = 1;
	}
	matrix = new CompressedSparseRows(dimensions[0], dimensions[1], upperTriangle);
	Matrix* matrixL = new CompressedSparseRows(dimensions[0], dimensions[1], lowerTriangle);
	matrices = new std::vector<Matrix*>();
	matrices->push_back(matrixL);
	matrices->push_back(matrix);


	delete lowerTriangle;
	delete upperTriangle;
}

void FactorizationFactory::LDUFactorization(Matrix* matrix)
{
	int* dimensions{ matrix->GetMatrixDimensions() };
	std::vector<double>* lowerTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	std::vector<double>* upperTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	std::vector<double>* diagonalTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);

	for (size_t i = 0; i < dimensions[0]; i++)
	{
		for (size_t j = 0; j < dimensions[1]; j++)
		{
			double sum{ 0 };
			if (i == j)
			{
				for (size_t k = 0; k < i; k++)
				{
					sum += lowerTriangle->at(i * dimensions[1] + k) * upperTriangle->at(k * dimensions[1] + i) * diagonalTriangle->at(k * dimensions[1] + k);
				}
				diagonalTriangle->at(i * dimensions[1] + j) = matrix->FindValue(i, i) - sum;
			}
			else if (i > j)
			{
				for (size_t k = 0; k < j; k++)
				{
					sum += lowerTriangle->at(i * dimensions[1] + k) * upperTriangle->at(k * dimensions[1] + j) * diagonalTriangle->at(k * dimensions[1] + k);
				}
				lowerTriangle->at(i * dimensions[1] + j) = (matrix->FindValue(i, j) - sum) / diagonalTriangle->at(j * dimensions[1] + j);
			}
			else
			{
				for (size_t k = 0; k < i; k++)
				{
					sum += lowerTriangle->at(i * dimensions[1] + k) * upperTriangle->at(k * dimensions[1] + j) * diagonalTriangle->at(k * dimensions[1] + k);
				}
				upperTriangle->at(i * dimensions[1] + j) = (matrix->FindValue(i, j) - sum) / diagonalTriangle->at(i * dimensions[1] + i);
			}
		}
	}

	for (size_t i = 0; i < dimensions[0]; i++)
	{
		lowerTriangle->at(i * dimensions[1] + i) = 1;
		upperTriangle->at(i * dimensions[1] + i) = 1;
	}
	//for (size_t i = 0; i < dimensions[0]; i++)
	//{
	//	for (size_t j = 0; j < dimensions[1]; j++)
	//	{
	//		upperTriangle->push_back(matrix->FindValue(i, j));
	//	}
	//}
	//for (size_t i = 0; i < dimensions[0] - 1; i++)
	//{
	//	for (size_t j = i + 1; j < dimensions[0]; j++)
	//	{
	//		double newValue{ upperTriangle->at(j * dimensions[1] + i) / upperTriangle->at(i * dimensions[1] + i) };
	//		lowerTriangle->at(j * dimensions[1] + i) = newValue;

	//		for (size_t k = i; k < dimensions[0]; k++)
	//		{
	//			newValue = upperTriangle->at(j * dimensions[1] + k) - lowerTriangle->at((j * dimensions[1] + i)) * upperTriangle->at(i * dimensions[1] + k);
	//			upperTriangle->at(j * dimensions[1] + k) = newValue;
	//		}
	//	}
	//}
	//for (size_t i = 0; i < dimensions[0]; i++)
	//{
	//	lowerTriangle->at(i * dimensions[1] + i) = 1;
	//	for (size_t j = i; j < dimensions[1]; j++)
	//	{
	//		if (i == j)
	//		{
	//			diagonalTriangle->at(i * dimensions[1] + j) = upperTriangle->at(i * dimensions[1] + j);
	//		}
	//		upperTriangle->at(i * dimensions[1] + j) /= upperTriangle->at(i * dimensions[1] + i);
	//	}
	//}

	matrix = new CompressedSparseRows(dimensions[0], dimensions[1], upperTriangle);
	Matrix* matrixL = new CompressedSparseRows(dimensions[0], dimensions[1], lowerTriangle);
	Matrix* matrixD = new DiagonalMatrix(dimensions[0], dimensions[1], diagonalTriangle);
	matrices = new std::vector<Matrix*>();
	matrices->push_back(matrixL);
	matrices->push_back(matrixD);
	matrices->push_back(matrix);

	delete lowerTriangle;
	delete upperTriangle;
	delete diagonalTriangle;
}

void FactorizationFactory::CholeskyFactorization(Matrix* matrix)
{
	int* dimensions{ matrix->GetMatrixDimensions() };
	std::vector<double>* lowerTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	for (size_t i = 0; i < dimensions[0]; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < j; k++)
			{
				sum += lowerTriangle->at(i * dimensions[1] + k) * lowerTriangle->at(j * dimensions[1] + k);
			}
			if (i == j)
			{
				lowerTriangle->at(i * dimensions[1] + j) = sqrt(matrix->FindValue(i, j) - sum);
			}
			else
			{
				lowerTriangle->at(i * dimensions[1] + j) = (1 / lowerTriangle->at(j * dimensions[1] + j) * (matrix->FindValue(i, j) - sum));
			}
		}
	}
	matrix = new CompressedSparseRows(dimensions[0], dimensions[1], lowerTriangle);
	matrices = new std::vector<Matrix*>();
	matrices->push_back(matrix);

	delete lowerTriangle;
}

void FactorizationFactory::LDLFactorization(Matrix* matrix)
{
	int* dimensions{ matrix->GetMatrixDimensions() };
	std::vector<double>* lowerTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	std::vector<double>* diagonalTriangle = new std::vector<double>(dimensions[0] * dimensions[1], 0);
	for (size_t j = 0; j < dimensions[1]; j++)
	{

		for (int i = j; i < dimensions[0]; i++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < j; k++)
			{
				sum += lowerTriangle->at(i * dimensions[1] + k) * lowerTriangle->at(j * dimensions[1] + k) * diagonalTriangle->at(k * numOfCols + k);
			}
			double newValue{ matrix->FindValue(i, j) - sum };
			if (i == j)
			{
				diagonalTriangle->at(i * dimensions[1] + j) = newValue;
				lowerTriangle->at(i * dimensions[1] + j) = 1;
			}
			else
			{
				lowerTriangle->at(i * dimensions[1] + j) = newValue / diagonalTriangle->at(j * dimensions[1] + j);
			}
		}
	}

	matrix = new CompressedSparseRows(dimensions[0], dimensions[1], lowerTriangle);
	Matrix* matrixD = new DiagonalMatrix(dimensions[0], dimensions[1], diagonalTriangle);
	matrices = new std::vector<Matrix*>();
	matrices->push_back(matrix);
	matrices->push_back(matrixD);

	delete lowerTriangle;
	delete diagonalTriangle;
}

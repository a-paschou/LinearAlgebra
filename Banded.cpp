#include "Banded.h"
#include <stdexcept>
#include <iostream>

Banded::Banded(int numOfRows, int numOfCols, std::vector<double>* values)
	//:numOfRows{ static_cast<const unsigned int>(numOfRows) }, numOfCols{ static_cast<const unsigned int>(numOfCols) }, isSymmetric{ true }
{
	if (values->size() != (numOfRows * numOfCols))
	{
		throw std::invalid_argument("The dimensions and the number of values of the matrix do not match.");
	}
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;
	this->isSymmetric = true;

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

void Banded::StoreSymmetricValues(std::vector<double>* values)
{
	this->values = new std::vector<double>();
	height[0] = std::min(numOfRows, numOfCols) - 1;
	height[1] = std::min(numOfRows, numOfCols) - 1;
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			if ((i + j) <= (numOfCols - 1))
			{
				this->values->push_back(values->at(j * numOfCols + (i + j)));
			}
			else
			{
				this->values->push_back(0.0);
			}
		}
	}

	for (size_t i = (this->values->size() - 1); i >= (numOfRows - 1); i -= numOfRows)
	{
		int temp{ 0 };
		for (size_t j = 0; j < numOfRows; j++)
		{
			if (this->values->at(i - j) == 0)
			{
				temp += 1;
			}
		}
		if (temp == numOfRows)
		{
			for (size_t j = 0; j < numOfRows; j++)
			{
				std::vector<double>::iterator it{ this->values->begin() + this->values->size() - 1 };
				this->values->erase(it);
			}
			height[0] -= 1;
			height[1] -= 1;
		}
		if (temp == 0)
		{
			break;
		}
	}
}

void Banded::StoreNonSymmetricValues(std::vector<double>* values)
{
	this->values = new std::vector<double>();
	height[0] = std::min(numOfRows, numOfCols) - 1;
	height[1] = std::min(numOfRows, numOfCols) - 1;
	for (int i = static_cast<int>(numOfRows - 1); i >= 0; i--)
	{
		for (int j = -i; j <= static_cast<int>(numOfCols - 1 - i); j++)
		{
			if (j < 0)
			{
				this->values->push_back(0.0);
			}
			else
			{
				this->values->push_back(values->at((i + j) * numOfCols + j));
			}
		}
	}

	for (size_t i = 0; i <= (this->values->size() - 1); i += numOfRows)
	{
		int temp{ 0 };
		for (size_t j = 0; j < numOfRows; j++)
		{
			if (this->values->at(i + j) == 0)
			{
				temp += 1;
			}
		}
		if (temp == numOfRows)
		{
			for (size_t j = 0; j < numOfRows; j++)
			{
				std::vector<double>::iterator it{ this->values->begin() + i };
				this->values->erase(it);
			}
			height[0] -= 1;
		}
	}

	std::vector<double> upperTriangle{};
	for (size_t i = 1; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfCols; j++)
		{
			if ((i + j) <= (numOfCols - 1))
			{
				upperTriangle.push_back(values->at(j * numOfCols + (i + j)));
			}
			else
			{
				upperTriangle.push_back(0.0);
			}
		}
	}

	for (int i = (static_cast<int>(upperTriangle.size()) - 1); i >= static_cast<int>(numOfRows - 1); i -= static_cast<int>(numOfRows))
	{
		int temp{ 0 };
		for (size_t j = 0; j < numOfRows; j++)
		{
			if (upperTriangle.at(i - j) == 0)
			{
				temp += 1;
			}
		}
		if (temp == numOfRows)
		{
			for (size_t j = 0; j < numOfRows; j++)
			{
				std::vector<double>::iterator it{ upperTriangle.begin() + upperTriangle.size() - 1 };
				upperTriangle.erase(it);
			}
			height[1] -= 1;
		}
		if (temp == 0)
		{
			break;
		}
	}

	for (auto const& val : upperTriangle)
	{
		this->values->push_back(val);
	}
}

double Banded::FindValue(int row, int col)
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

double Banded::ReturnValueFromSymmetricMatrix(int row, int col)
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
	int numOfDiag{ std::min(numOfRows, numOfCols) };
	int diff{ col - row };
	return diff * numOfDiag + row < this->values->size() ? values->at(diff * numOfDiag + row) : 0.0;
}

double Banded::ReturnValueFromNonSymmetricMatrix(int row, int col)
{
	int numOfDiag{ std::min(numOfRows, numOfCols) };
	if (row >= col)
	{
		int diff{ row - col };
		return (height[0] - diff) >= 0 ? values->at((height[0] - diff) * numOfDiag + row) : 0.0;
	}
	else
	{
		int diff{ col - row };
		return (height[1] - diff) >= 0 ? values->at((height[0] + diff) * numOfDiag + row) : 0.0;
	}
}

Matrix* Banded::MatrixByMatrixMultiplication(Matrix& rightMatrix)
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
	Banded* newMatrix = new Banded(numOfRows, rightMatrix.numOfCols, newValues);
	return newMatrix;
}

Matrix* Banded::MatrixAddition(Matrix& rightMatrix)
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
	Banded* newMatrix = new Banded(numOfRows, numOfCols, newValues);
}

Matrix* Banded::Transpose()
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
		Matrix* newMatrix = new Banded(numOfCols, numOfRows, transposedValues);
		delete transposedValues;
		return newMatrix;
	}
}

Banded::~Banded()
{
	std::cout << "Calling Destructor" << std::endl;
}

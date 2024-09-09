#include "MatrixUtil.h"
#include <iostream>

void MatrixUtil::PrintMatrix(Matrix& matrix)
{
	for (size_t i = 0; i < matrix.numOfRows; i++)
	{
		for (size_t j = 0; j < matrix.numOfCols; j++)
		{
			std::cout << matrix.FindValue(i, j);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

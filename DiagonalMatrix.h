#pragma once
#include "Matrix.h"
class DiagonalMatrix : public Matrix
{
public:
	DiagonalMatrix(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~DiagonalMatrix();
};


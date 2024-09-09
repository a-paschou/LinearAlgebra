#pragma once
#include <vector>
#include "Matrix.h"
//Saves a matrix in full storage format. It follows row major ordering.
class FullStorageFormat : public Matrix
{
private:
	//const int numOfRows;
	//const int numOfCols;
	//std::vector<double>* values;
public:
	FullStorageFormat(const int, const int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~FullStorageFormat();
};


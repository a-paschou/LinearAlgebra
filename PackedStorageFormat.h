#pragma once
#include <vector>
#include "Matrix.h"
//Saves the upper triangular of a symmetric matrix. It follows row major ordering.
class PackedStorageFormat : public Matrix
{
protected:
	//const int numOfRows;
	//const int numOfCols;
	//std::vector<double>* values;
public:
	PackedStorageFormat(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~PackedStorageFormat();
};


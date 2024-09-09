#pragma once
#include <vector>
#include "Matrix.h"
//Saves the matrix in a coordinate list. It follows row major ordering.
class CoordinateList : public Matrix
{
private:
	//const int numOfRows;
	//const int numOfCols;
	//std::vector<int>* rows;
	//std::vector<int>* cols;
	//std::vector<int>* values;
public:
	CoordinateList(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~CoordinateList();
};


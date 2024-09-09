#pragma once
#include <vector>
#include "Matrix.h"
//Saves a matrix in compressed sparse columns format. It follows the row major ordering.
class CompressedSparseColumns : public Matrix
{
private:
	//const int numOfRows;
	//const int numOfCols;
	//std::vector<int>* colOffsets;
	//std::vector<int>* rowIndices;
	//std::vector<double>* values;
public:
	CompressedSparseColumns(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~CompressedSparseColumns();
};


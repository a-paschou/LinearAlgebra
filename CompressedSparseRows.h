#pragma once
#include <vector>
#include "Matrix.h"
//Saves a matrix in compressed sparse rows format. It follows the row major ordering.
class CompressedSparseRows : public Matrix
{
private:
	//const int numOfRows;
	//const int numOfCols;
	//std::vector<int>* colIndices;
	//std::vector<int>* rowOffsets;
	//std::vector<double>* values;
public:
	CompressedSparseRows(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~CompressedSparseRows();
};


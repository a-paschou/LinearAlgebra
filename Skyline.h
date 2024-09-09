#pragma once
#include <vector>
#include "Matrix.h"
// Stores the matrix in Skyline format. It currenty works for symmetric matrices.
class Skyline : public Matrix
{
private:
	//const unsigned int numOfRows;
	//const unsigned int numOfCols;
	//std::vector<double>* values;
	/*std::vector<int>* diagOfSets;
	std::vector<int>* heights;*/
	void StoreSymmetricValues(std::vector<double>*);
	void StoreNonSymmetricValues(std::vector<double>*);
	double ReturnValueFromSymmetricMatrix(int, int);
	double ReturnValueFromNonSymmetricMatrix(int, int);
public:
	Skyline(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~Skyline();
};


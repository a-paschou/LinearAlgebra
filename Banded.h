#pragma once
#include <vector>
#include "Matrix.h"
//Saves a matrix in banded format.
class Banded : public Matrix
{
private:
	/*const unsigned int numOfRows;
	const unsigned int numOfCols;
	int height[2]{ 0, 0 };
	bool isSymmetric;*/
	//std::vector<double>* values;
	void StoreSymmetricValues(std::vector<double>*);
	void StoreNonSymmetricValues(std::vector<double>*);
	double ReturnValueFromSymmetricMatrix(int, int);
	double ReturnValueFromNonSymmetricMatrix(int, int);
public:
	Banded(int, int, std::vector<double>*);
	virtual double FindValue(int, int) override final;
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&) override final;
	virtual Matrix* MatrixAddition(Matrix&) override final;
	virtual Matrix* Transpose() override final;
	~Banded();
};


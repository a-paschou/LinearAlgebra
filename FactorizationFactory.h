#pragma once
#include "Matrix.h"
#include "FactorizationType.h"
class FactorizationFactory : public Matrix
{
public:
	std::vector<Matrix*>* matrices = nullptr;
	FactorizationFactory(Matrix*, FactorizationType);
	void LUFactorization(Matrix*);
	void LDUFactorization(Matrix*);
	void CholeskyFactorization(Matrix*);
	void LDLFactorization(Matrix*);
};


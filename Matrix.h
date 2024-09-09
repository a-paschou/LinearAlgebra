#pragma once
#include <vector>

class Matrix
{
	friend class FullStorageFormat;
	friend class PackedStorageFormat;
	friend class CoordinateList;
	friend class CompressedSparseRows;
	friend class CompressedSparseColumns;
	friend class Banded;
	friend class Skyline;
	friend class DiagonalMatrix;
protected:
	int numOfRows = 0;
	int numOfCols = 0;
	std::vector<double>* values = nullptr;
	std::vector<int>* rows = nullptr;
	std::vector<int>* cols = nullptr;
	std::vector<int>* colIndices = nullptr;
	std::vector<int>* rowOffsets = nullptr;
	std::vector<int>* colOffsets = nullptr;
	std::vector<int>* rowIndices = nullptr;
	int height[2]{ 0, 0 };
	bool isSymmetric = true;
	std::vector<int>* diagOfSets = nullptr;
	std::vector<int>* heights = nullptr;
	virtual void CheckSymmetry(int, int, std::vector<double>*);
public:
	Matrix();
	Matrix* CreateMatrix();
	virtual double FindValue(int, int);
	virtual Matrix* MatrixByMatrixMultiplication(Matrix&);
	virtual Matrix* MatrixAddition(Matrix&);
	virtual Matrix* Transpose();
	virtual void PrintMatrix();
	virtual int* GetMatrixDimensions();
	~Matrix();
};


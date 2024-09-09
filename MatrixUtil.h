#pragma once
#include "Matrix.h"
class MatrixUtil
{
	friend class FullStorageFormat;
	friend class PackedStorageFormat;
	friend class CoordinateList;
	friend class CompressedSparseRows;
	friend class CompressedSparseColumns;
	friend class Banded;
	friend class Skyline;
public:
	static void PrintMatrix(Matrix&);
};


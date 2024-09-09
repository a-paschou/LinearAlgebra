// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
//#include "FullStorageFormat.h"
//#include "PackedStorageFormat.h"
//#include "CoordinateList.h"
//#include "CompressedSparseRows.h"
//#include "CompressedSparseColumns.h"
//#include "Banded.h"
//#include "Skyline.h"
//#include "FactorizationFactory.h"
//#include "ISolver.h"
//#include "Solver.h"
//#include "DirectSolution.h"
//#include "GradientBased.h"
//#include "Analyzer.h"

int main()
{
//#pragma region Creation and computations of matrices
//	// FULL STORAGE FORMAT
//	const int rows = 3;
//	const int cols = 4;
//	std::vector<double> values1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
//	std::vector<double> values2{ 2, 3, -1, 0, 4, 7, -2, 9, 8, 15, 1, -3 };
//	Matrix* matrix1 = new FullStorageFormat(rows, cols, &values1);
//	Matrix* matrix2 = new FullStorageFormat(cols, rows, &values2);
//	Matrix* matrix3 = new FullStorageFormat(rows, cols, &values2);
//
//	Matrix* productMatrix = matrix1->MatrixByMatrixMultiplication(*matrix2);
//	Matrix* summationMatrix = matrix1->MatrixAddition(*matrix3);
//	std::cout << std::endl;
//	std::cout << "FULL STORAGE FORMAT" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	productMatrix->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "Summation" << std::endl;
//	summationMatrix->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix1;
//	delete matrix2;
//	delete productMatrix;
//	delete summationMatrix;
//
//	//PACKED STORAGE FORMAT
//	int dimension{ 4 };
//	std::vector<double> values3{ 1 , 5 , 2, -3, 5, 2, 6, 7, 2, 6, -4, 1, -3, 7, 1, 9 };
//	std::vector<double> values4{ 7, 2, -5, 3, 2, 1, 8, 4, -5, 8, -3, 6, 3, 4, 6, 1 };
//	Matrix* matrix4 = new PackedStorageFormat(dimension, dimension, &values3);
//	Matrix* matrix5 = new PackedStorageFormat(dimension, dimension, &values4);
//
//	Matrix* matrix6 = matrix4->MatrixByMatrixMultiplication(*matrix5);
//	Matrix* matrix7 = matrix4->MatrixAddition(*matrix5);
//
//	std::cout << std::endl;
//	std::cout << "PACKED STORAGE FORMAT" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix6->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "Summation" << std::endl;
//	matrix7->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix4;
//	delete matrix5;
//	delete matrix6;
//	delete matrix7;
//
//	//COORDINATE LIST
//	std::vector<double> values5{ 9, 0, 3, 0, 0, 8, 0, 0, 0, 2, 6, 0, 1, 0, 0, 5 };
//	std::vector<double> values6{ 2, 3, 0, 5, 0, 1, 0, 0, 6, 2, 4, 0, 0, 1, 0, 3 };
//	Matrix* matrix8 = new CoordinateList(dimension, dimension, &values5);
//	Matrix* matrix9 = new CoordinateList(dimension, dimension, &values6);
//
//	Matrix* matrix10 = matrix8->MatrixByMatrixMultiplication(*matrix9);
//	Matrix* matrix11 = matrix8->MatrixAddition(*matrix9);
//
//	std::cout << std::endl;
//	std::cout << "COORDINATE LIST" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix10->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "Summation" << std::endl;
//	matrix11->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix8;
//	delete matrix9;
//	delete matrix10;
//	delete matrix11;
//
//	//COMPRESSED SPARSE ROWS
//	Matrix* matrix12 = new CompressedSparseRows(dimension, dimension, &values5);
//	Matrix* matrix13 = new CompressedSparseRows(dimension, dimension, &values6);
//
//	Matrix* matrix14 = matrix12->MatrixByMatrixMultiplication(*matrix13);
//	Matrix* matrix15 = matrix12->MatrixAddition(*matrix13);
//
//	std::cout << std::endl;
//	std::cout << "COMPRESSED SPARSE ROWS" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix14->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "Summation" << std::endl;
//	matrix15->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix12;
//	delete matrix13;
//	delete matrix14;
//	delete matrix15;
//
//	//COMPRESSED SPARSE COLUMNS
//	Matrix* matrix16 = new CompressedSparseColumns(dimension, dimension, &values5);
//	Matrix* matrix17 = new CompressedSparseColumns(dimension, dimension, &values6);
//
//	Matrix* matrix18 = matrix16->MatrixByMatrixMultiplication(*matrix17);
//	Matrix* matrix19 = matrix16->MatrixAddition(*matrix17);
//
//	std::cout << std::endl;
//	std::cout << "COMPRESSED SPARSE COLUMNS" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix18->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "Summation" << std::endl;
//	matrix19->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix16;
//	delete matrix17;
//	delete matrix18;
//	delete matrix19;
//
//	//BANDED
//	std::vector<double> values7{ 21, 1, 0, 4, 0, 1, 22, 2, 0, 0, 0, 2, 23, 1, 3, 4, 0, 1, 24, 2, 0, 0, 3, 2, 25 };
//	//std::vector<double> values8{ 5, 2, 12, 1, 0, 2, 6, -2, 0, 0, 12, -2, 3, 8, -1, 1, 0, 8, 7, 5, 0, 0, -1, 5, 9 };
//	std::vector<double> values8{ 1, 2, 7, 0, 0, 8, 6, -1, 4, 0, 2, 2, 7, -3, 9, 7, -6, 5, 5, 1, 0, 2, -1, -8, 1 };
//	dimension = 5;
//	Matrix* matrix20 = new Banded(dimension, dimension, &values7);
//	Matrix* matrix21 = new Banded(dimension, dimension, &values8);
//	Matrix* matrix22 = matrix20->MatrixByMatrixMultiplication(*matrix21);
//	Matrix* matrix23 = matrix20->MatrixAddition(*matrix21);
//
//	std::cout << std::endl;
//	std::cout << "BANDED" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix22->PrintMatrix();
//	std::cout << "Summation" << std::endl;
//	std::cout << std::endl;
//	matrix23->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix20;
//	delete matrix21;
//	delete matrix22;
//	delete matrix23;
//
//	//SKYLINE
//	std::vector<double> values9 = { 1, 6, 0, 0, 13, 6, 2, 7, 9, 12, 0, 7, 3, 8, 11, 0, 9, 8, 4, 10, 13, 12, 11, 10, 5 };
//	Matrix* matrix24 = new Skyline(dimension, dimension, &values7);
//	Matrix* matrix25 = new Skyline(dimension, dimension, &values9);
//	Matrix* matrix26 = matrix24->MatrixByMatrixMultiplication(*matrix25);
//	Matrix* matrix27 = matrix24->MatrixAddition(*matrix25);
//
//	std::cout << std::endl;
//	std::cout << "SKYLINE" << std::endl;
//	std::cout << "Multiplication" << std::endl;
//	matrix26->PrintMatrix();
//	std::cout << "Summation" << std::endl;
//	std::cout << std::endl;
//	matrix27->PrintMatrix();
//	std::cout << "=================================" << std::endl;
//	delete matrix24;
//	delete matrix25;
//	delete matrix26;
//	delete matrix27;
//#pragma endregion
//
//#pragma region Matrix factorization
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//	std::cout << "MATRIX FACTORIZATION" << std::endl;
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//
//	std::cout << "LU DECOMPOSITION" << std::endl;
//	Matrix* decomposition = new Skyline(dimension, dimension, &values7);
//	FactorizationFactory* factory = new FactorizationFactory(decomposition, FactorizationType::LU);
//	std::cout << "L Matrix" << std::endl;
//	factory->matrices->at(0)->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "U Matrix" << std::endl;
//	factory->matrices->at(1)->PrintMatrix();
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//
//	std::cout << "LDU DECOMPOSITION" << std::endl;
//	decomposition = new Skyline(dimension, dimension, &values7);
//	factory = new FactorizationFactory(decomposition, FactorizationType::LDU);
//	std::cout << "L Matrix" << std::endl;
//	factory->matrices->at(0)->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "D Matrix" << std::endl;
//	factory->matrices->at(1)->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "U Matrix" << std::endl;
//	factory->matrices->at(2)->PrintMatrix();
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//
//	std::cout << "CHOLESKY DECOMPOSITION" << std::endl;
//	decomposition = new Skyline(dimension, dimension, &values7);
//	factory = new FactorizationFactory(decomposition, FactorizationType::Cholesky);
//	std::cout;
//	std::cout << "L Matrix" << std::endl;
//	factory->matrices->at(0)->PrintMatrix();
//	std::cout << "====================" << std::endl;
//	std::cout << "====================" << std::endl;
//
//	std::cout << "LDL DECOMPOSITION" << std::endl;
//	decomposition = new Skyline(dimension, dimension, &values7);
//	factory = new FactorizationFactory(decomposition, FactorizationType::LDL);
//	std::cout << "L Matrix" << std::endl;
//	factory->matrices->at(0)->PrintMatrix();
//	std::cout << std::endl;
//	std::cout << "D Matrix" << std::endl;
//	factory->matrices->at(1)->PrintMatrix();
//
//	delete decomposition;
//	delete factory;
//
//#pragma endregion
//
//#pragma region Direct Solver
//	int dim{ 5 };
//	std::vector<double> rhs{ 1, 2, 3, 4, 5 };
//	Matrix* lhs = new Skyline(dim, dim, &values7);
//
//	//Solver<DirectSolution>* solver = new Solver<DirectSolution>(&rhs, lhs);
//	//solver->Solve();
//
//	Model* model = new Model(lhs, &rhs);
//	Analyzer* analyzer1 = new Analyzer(model, new DirectSolution(FactorizationType::LU));
//	analyzer1->Solve();
//
//	analyzer1->ChangeSolver(new DirectSolution(FactorizationType::LDU));
//	analyzer1->Solve();
//
//	analyzer1->ChangeSolver(new DirectSolution(FactorizationType::Cholesky));
//	analyzer1->Solve();
//
//	analyzer1->ChangeSolver(new DirectSolution(FactorizationType::LDL));
//	analyzer1->Solve();
//
//	std::cout << std::endl;
//#pragma endregion

}
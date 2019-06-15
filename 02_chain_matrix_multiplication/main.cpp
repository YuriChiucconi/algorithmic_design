#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "chain_matrix_class.cpp"

using namespace std::chrono;

int main()
{
	int a = 500;
	int b = 32;
	int c = 15;
	int d = 878;
	int e = 300;
	int f = 926;
	
	Matrix<double> A0 = Matrix<double>(a, b);
	Matrix<double> A1 = Matrix<double>(b, b);
	Matrix<double> A2 = Matrix<double>(b, d);
	Matrix<double> A3 = Matrix<double>(d, e);
	Matrix<double> A4 = Matrix<double>(e, f);

	ChainMatrix<double> C = ChainMatrix<double>(5);

	A0.random();
	A1.random();
	A2.random();
	A3.random();
	A4.random();

	C.add(A0);
	C.add(A1);
	C.add(A2);
	C.add(A3);
	C.add(A4);



	// DYNAMIC

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	Matrix<double> M1 = C.multiply();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	// M1.print();

	duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
	std::cout << "DYNAMIC: " << time_span1.count() << " seconds." << std::endl;


	// STANDARD

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	Matrix<double> M2 = C.standard_multiply();
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	// M2.print();
	
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
	std::cout << "STANDARD: " << time_span2.count() << " seconds." << std::endl;

	std::cin.get();
}
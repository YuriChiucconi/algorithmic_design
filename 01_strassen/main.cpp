#include <iostream>

#include <ctime>
#include <ratio>
#include <chrono>

#include "matrix_class.cpp"

int main()
{

	int n = 1024;
	int m = 1024;
	int l = 1024;

	Matrix a = Matrix(n, m);
	Matrix b = Matrix(m, l);

	a.random();
	b.random();

	using namespace std::chrono;

// STRASSEN

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	Matrix c = a.strassen(b);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);

	std::cout << "STRASSEN: " << time_span1.count() << " seconds." << std::endl;


// STANDARD

	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	Matrix d = a*b;

	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

	std::cout << "STANDARD: " << time_span2.count() << " seconds." << std::endl;

	std::cin.get();
}
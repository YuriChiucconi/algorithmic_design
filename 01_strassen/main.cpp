#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "matrix_class.cpp"

using namespace std::chrono;

int main()
{
	int a = 4;
	int b = 4;
	int c = 4;
	
	high_resolution_clock::time_point s;
	high_resolution_clock::time_point t;
	duration<double> time_span;

	for (int i = 0; i < 10; i++)
	{
		Matrix<double>* A = new Matrix<double>(a, b);
		Matrix<double>* B = new Matrix<double>(b, c);

		s = high_resolution_clock::now();

		*A * *B;

		t = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t - s);

		std::cout << "DIM: 2^(" << 2 + i << ")\tStandard: " << time_span.count();

		s = high_resolution_clock::now();

		(*A).strassen(*B);

		t = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t - s);

		std::cout << "\tStrassen: " << time_span.count() << std::endl;

		a *= 2;
		b *= 2;
		c *= 2;

		delete A;
		delete B;
	}

	std::cin.get();
}
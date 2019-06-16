#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <math.h>

#include "min_heap_class.cpp"
using namespace std::chrono;


void build_heap(int* vector, int dim)
{
	int tmp;
	for (int i = dim - 1; i > 0; --i)
	{
		if (vector[i] <= vector[(i - 1) / 2])
		{
			tmp = vector[(i - 1) / 2];
			vector[(i - 1) / 2] = vector[i];
			vector[i] = tmp;
		}
	}
	return;
}

min_heap* make_new_heap(int* vector, int dim)
{
	build_heap(&vector[0], dim);


	min_heap* ret = new min_heap(dim);
	for (int i = 0; i < dim; ++i)
	{
		ret->insert(vector[i]);
	}

	return ret;
}
int* random(int dim, unsigned int max = 1000)
{
	int* v = new int[dim];

	for (int i = 0; i < dim; ++i)
	{
		v[i] = rand() % max;
	}
	return v;
}

int main()
{
	int max = 27;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> time_span;
	int aux;

	for (int i = 1; i < max; i++)
	{

		std::cout << "n = 2^" << i << "\t";

		int* v = random(pow(2, i));

		// BUILDING - O(n)

		t1 = high_resolution_clock::now();
		build_heap(v, pow(2, i));
		t2 = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "BUILDING " << time_span.count() << "\t";

		min_heap* tmp = make_new_heap(v, pow(2, i));
		delete[] v;


		// EXTRACTING - O(log n)
		t1 = high_resolution_clock::now();
		aux = tmp->extract_next();
		t2 = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "EXTRACTING " << time_span.count() << "\t";

		
		// INSERTING O(log n)
		t1 = high_resolution_clock::now();
		tmp->insert(aux);
		t2 = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "INSERTING " << time_span.count() << "\t";
		
		// DECREASING O(log n)
		t1 = high_resolution_clock::now();
		tmp->decrease_key(pow(2, i) - 1, 0);
		t2 = high_resolution_clock::now();

		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << "DECREASING " << time_span.count() << "\n\n\n";
		
		
		delete tmp;
	}


	std::cin.get();
	return 0;
}
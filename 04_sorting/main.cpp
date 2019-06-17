#include <iostream>

#include <time.h>    // time() 
#include <ctime>
#include <ratio>
#include <chrono>

#include "vector_class.cpp"

using namespace std::chrono;

int main()
{
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> time_span;

///////// Prove by testing that both Insertion Sort and Quick Sort take time
/////////  O(n^ 2) in the worst case
/////////  O(n) and O(n log n), respectively, in the best case

	std::cout << "n\tINSERT.(w)\tQUICK(w)\tINSERTI.(b)\tQUICK(b)\n\n";
	for (int i = 1; i < 20; ++i)
	{
		std::cout << "2^" << i << "\t";
		vector* V = new vector(static_cast<int>(pow(2, i)));

		///////////////// INSERTION SORT worst
		
		V->worst();
		
		t1 = high_resolution_clock::now();
		V->insertion_sort();
		t2 = high_resolution_clock::now();

		
		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << time_span.count() << "\t";

		///////////////// QUICK SORT worst

		V->worst();

		t1 = high_resolution_clock::now();
		V->quick_sort();
		t2 = high_resolution_clock::now();


		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << time_span.count() << "\t";
		

		///////////////// INSERTION SORT best

		V->best();

		t1 = high_resolution_clock::now();
		V->insertion_sort();
		t2 = high_resolution_clock::now();


		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << time_span.count() << "\t";

		///////////////// QUICK SORT best

		V->best();

		t1 = high_resolution_clock::now();
		V->quick_sort();
		t2 = high_resolution_clock::now();


		time_span = duration_cast<duration<double>>(t2 - t1);
		std::cout << time_span.count() << "\n\n";


		delete V;
	}

	std::cin.get();
}
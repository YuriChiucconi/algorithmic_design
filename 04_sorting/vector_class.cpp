#include <iostream>
#include <stdlib.h>  // rand()

class vector
{
	int* v;
	int n;

	int max;

private:

	void invalid()
	{
		for (int i = 0; i < n; i++)
		{
			v[i] = -1;
		}
		return;
	}

	void set_n(int dim)
	{
		if (v == nullptr)
		{
			this->n = dim;
			v = new int[dim];
			this->invalid();
		}
		return;
	}

public:

	vector()
		: v(nullptr), n(0), max(0) {}

	vector(int dim)
		: v(new int[dim]), n(dim), max(-1)
	{
		invalid();
	}

	~vector()
	{
		if (v != nullptr)
		{
			delete[] v;
		}
	}

	void print()
	{
		for (int i = 0; i < n; ++i)
		{
			std::cout << v[i] << "\t";
		}
		std::cout << "\n";
		return;
	}

	void print(int a, int b)
	{
		if (b <= a)
		{
			throw - 1;
		}
		for (int i = a; i < b; ++i)
		{
			std::cout << v[i] << "\t";
		}
		std::cout << "\n";
		return;
	}

	void zero()
	{
		for (int i = 0; i < n; ++i)
		{
			v[i] = 0;
		}
		max = 0;
		return;
	}

	void random(int maximum = 100)
	{
		if (maximum == 0)
		{
			return this->zero();
		}
		max = maximum;
		for (int i = 0; i < n; ++i)
		{
			v[i] = rand() % max;
		}
		return;
	}

	void worst()
	{
		for (int i = 0; i < n; ++i)
		{
			v[i] = n - i;
		}
		return;
	}

	void best()
	{
		for (int i = 0; i < n; ++i)
		{
			v[i] = i;
		}
		return;
	}

	/// SORTING ALGORITHMS

private:

	void swap(int i, int j)
	{
		int tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}

	void quick_sort_aux(int a, int b)
	{
		if (b - a < 2)
		{
			return;
		}
		if (b - a == 2)
		{
			if (v[a] > v[b - 1])
			{
				swap(a, b - 1);
			}
			return;
		}

		int pivot = a + (b - a) / 2;
		swap(pivot, b - 1);

		int j = b - 2;
		for (int i = 0; i < j; ++i)
		{
			if (v[i] > v[b - 1])
			{
				while (v[j] > v[b - 1])
				{
					j -= 1;
					if (j == i)
					{
						break;
					}
				}
				swap(i, j);
			}
		}
		if (v[j] <= v[b - 1])
		{
			j += 1;
		}
		swap(j, b - 1);

		quick_sort_aux(a, j);
		quick_sort_aux(j + 1, b);

		return;
	}

	int numDigits(int number)
	{
		int digits = 0;
		if (number == 0) digits = 1;

		while (number) {
			number /= 10;
			digits++;
		}
		return digits;
	}

	void counting_sort_exp(int e)
	{
		vector* output = new vector(n);
		vector* count = new vector(10);
		count->zero();
		int exp = static_cast<int>(pow(10, e));

		for (int i = 0; i < this->n; ++i)
		{
			count->v[(this->v[i] / exp) % 10]++;
		}


		for (int j = 1; j < 10; ++j)
		{
			count->v[j] += count->v[j - 1];
		}

		for (int i = n - 1; i >= 0; --i)
		{
			output->v[count->v[(this->v[i] / exp) % 10] - 1] = this->v[i];
			count->v[(this->v[i] / exp) % 10]--;
		}

		for (int i = 0; i < n; ++i)
		{
			this->v[i] = output->v[i];
		}

		delete count;
		delete output;
		return;

	};

	int select_aux(int i, int a, int b)
	{
		if (i < a || i >= b)
		{
			std::cerr << "ERRORE INDICE";
			throw - 1;
		}
		if (b - a < 2)
		{
			return v[a];
		}

		if (b - a == 2)
		{
			if (v[a + 1] < v[a])
			{
				swap(a, a + 1);
			}



			if (i == a)
			{
				return v[a];
			}
			else
			{
				return v[a + 1];
			}

		}


		int pivot = a + (b - a) / 2;
		swap(pivot, b - 1);
		int k = b - 2;
		for (int h = 0; h < k; h++)
		{
			if (v[h] > v[b - 1])
			{
				while (v[k] > v[b - 1])
				{
					k--;
					if (k == h)
					{
						break;
					}
				}
				swap(h, k);
			}
		}
		if (v[k] <= v[b - 1])
		{
			k++;
		}
		swap(k, b - 1);



		if (i == k)
		{
			return v[i];
		}
		else if (i < k)
		{
			return select_aux(i, a, k);
		}
		else
		{
			return select_aux(i, k + 1, b);
		}
	}

public:

	void insertion_sort()
	{
		for (int i = 1; i < n; ++i)
		{
			int k = i;
			int tmp;
			while (v[k] < v[k - 1] && k>0)
			{
				tmp = v[k];
				v[k] = v[k - 1];
				v[k - 1] = tmp;
				--k;
			}
		}
		return;
	}

	void quick_sort()
	{
		quick_sort_aux(0, n);
		return;
	}

	void counting_sort()
	{
		vector* C = new vector(max);
		C->zero();


		for (int i = 0; i < this->n; ++i)
		{
			C->v[this->v[i]] += 1;
		}


		for (int j = 1; j < C->n; ++j)
		{
			C->v[j] += C->v[j - 1];
		}

		int k = 0;
		int count = 0;
		for (int j = 0; j < C->n; ++j)
		{
			if (C->v[j] > k)
			{
				for (int h = 0; h < C->v[j] - k; ++h)
				{
					this->v[count + h] = j;
				}
				count += C->v[j] - k;
				k = C->v[j];
			}
		}

		delete C;
		return;
	};

	void radix_sort()
	{
		int d = numDigits(max);

		for (int i = 1; d - i > 0; ++i)
		{
			this->counting_sort_exp(i);
		}
	}

	void bucket_sort()
	{

		// creo un array di n vettori di dimensione n/2

		vector* buckets = new vector[n];

		for (int i = 0; i < n; ++i)
		{
			buckets[i].set_n(n / 2);
		}


		// scorro gli elementi di this->v e li metto nel bucket corretto

		int aux;
		int k;

		for (int i = 0; i < n; i++)
		{
			k = 0;
			aux = this->v[i];

			while (aux >= max / n)
			{
				aux -= max / n;
				k += 1;
			}

			for (int j = 0; j < n / 2; j++)
			{
				if (buckets[k].v[j] < 0)
				{
					buckets[k].v[j] = this->v[i];
					break;
				}
			}
		}


		// Ordino i bucket

		for (int b = 0; b < n; b++)
		{
			buckets[b].quick_sort();
		}


		// Scrivo gli elementi in ordine su this->v[i]

		int j = 0;
		for (int b = 0; b < n; b++)
		{
			for (int i = 0; i < n / 2; ++i)
			{
				if (buckets[b].v[i] >= 0)
				{
					this->v[j] = buckets[b].v[i];
					j++;
				}
			}
		}

		delete[] buckets;

	}

	int select(int i)
	{
		return select_aux(i, 0, n);
	}

};
#include <iostream>

class min_heap
{
	int* v;
	int n;
	int count;

private:

	int left(int i)
	{
		return 2 * i + 1;
	}

	int right(int i)
	{
		return 2 * i + 2;
	}

	int parent(int i)
	{
		return (i - 1) / 2;
	}

	void swap(int i, int j)
	{
		int tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
		return;
	}

	bool is_valid(int i)
	{
		return i < count;
	}

	int fix_heap(int i)
	{
		if (is_valid(right(i)))
		{
			if (v[right(i)] <= v[i] && v[right(i)] <= v[left(i)])
			{
				swap(i, right(i));
				return right(i);
			}
			else if (v[left(i)] <= v[i] && v[left(i)] <= v[right(i)])
			{
				swap(i, left(i));
				return left(i);
			}
			else
			{
				return count;
			}
		}
		else if (is_valid(left(i)))
		{
			if (v[left(i)] <= v[i])
			{
				swap(i, left(i));
				return left(i);
			}
		}
		else
		{
			return count;
		}
	}

public:

	min_heap()
		: v(nullptr), n(0), count(0) {}

	min_heap(int dim)
		: v(new int[dim]), n(dim), count(0) {}

	~min_heap()
	{
		if (v != nullptr)
		{
			delete[] v;
		}
	}


	void insert(int k)
	{
		if (count == n)
		{
			std::cout << "The HEAP if full\n\n";
			return;
		}

		v[count] = k;
		int i = count;
		count++;

		while (i != 0 && v[parent(i)] > v[i])
		{
			swap(i, parent(i));
			i = parent(i);
		}

		return;
	}

	int get_next()
	{
		return v[0];
	}

	int extract_next()
	{
		if (count == 0)
		{
			std::cout << "ERROR: zero values in the heap";
			throw - 1;
		}

		int ret = v[0];

		v[0] = v[count - 1];
		count--;


		// HEAPIFY
		int i = 0;
		while (is_valid(i))
		{
			i = fix_heap(i);
		}

		return ret;
	}

	void print()
	{
		for (int i = 0; i < count; i++)
		{
			std::cout << v[i] << "\t";
		}
		std::cout << "\n";
		return;
	}

	void heap_sort()
	{
		int k = count;
		int tmp;
		while (count > 0)
		{
			tmp = extract_next();
			for (int i = count; i < k - 1; ++i)
			{
				v[i] = v[i + 1];
			}

			v[k - 1] = tmp;
		}
		count = k;
		return;
	}

	void decrease_key(int index, int new_value)
	{
		if (index >= count)
		{
			std::cerr << "\n\nERROR: out of index!\n\n";
			return;
		}
		if (v[index] < new_value)
		{
			std::cerr << "\n\nERROR: the value is not decreasing!\n\n";
			return;
		}


		v[index] = new_value;
		while (index != 0 && v[index] < v[parent(index)])
		{
			swap(index, parent(index));
			index = parent(index);
		}

		return;
	}

	friend min_heap* make_new_heap(int* vector, int dim);

};



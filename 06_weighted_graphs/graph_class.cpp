#include <iostream>
#include <limits> // std::numeric_limits<int>::max()


class Graph
{
	struct edge
	{
		int key;
		int weight;
		edge* ptr;
		
		edge()
			: key(-1), weight(-1), ptr(nullptr) {}
		
		edge(int n, int w)
			: key(n), weight(w), ptr(nullptr) {}
		
		~edge() = default;
	};

	class adj_list
	{
		int dim;
		edge* list;

	public:
		
		adj_list()
			: dim(0), list(nullptr) {}
	
		adj_list(int n)
			: dim(n), list(new edge[n])
		{
			for (int i = 0; i < n; ++i)
			{
				list[i].key = i;
				list[i].weight = 0;
			}
		}
		
		void erase_list(edge* it)
		{
			if (it->ptr != nullptr)
			{
				erase_list(it->ptr);
			}
			if (it->ptr == nullptr)
			{
				return;
			}
			delete it->ptr;
			return;
		}
		
		~adj_list()
		{
			if (list != nullptr)
			{
				for (int i = 0; i < dim; i++)
				{
					if (list[i].ptr != nullptr)
					{
						erase_list(list[i].ptr);
					}
				}
				delete[] list;
			}
		}
	
		void add_edge(int a, int b, int weight) // edge between a and b with weight
		{
			if (a<0 || a>dim || a == b || b<0 || b>dim || weight < 0)
			{
				std::cout << "ERROR in adding edge!\n\n";
				throw - 1;
			}
			edge* it = &list[a];
			while (it->ptr != nullptr)
			{
				if (it->key == b)
				{
					std::cout << "Edge between" << a << " and " << b << " is already in the graph!\n\n";
					return;
				}
				it = it->ptr;
			}
			it->ptr = new edge(b,weight);
		}
		
		edge* operator[](int n)
		{
			if (n >= dim) { throw - 1; }
			
			return &(this->list[n]);
		}
		
	};

	struct tuple
	{
		int key;
		int distance;

		tuple()
			:key(-1), distance(-1) {}

		tuple(const tuple& b)
			: key(b.key), distance(b.distance) {}

		tuple(int k, int d)
			: key(k), distance(d) {}

	};

	struct tuple_heap
	{
		tuple* v;
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
			tuple tmp = v[i];
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
				if (v[right(i)].distance <= v[i].distance && v[right(i)].distance <= v[left(i)].distance)
				{
					swap(i, right(i));
					return right(i);
				}
				else if (v[left(i)].distance <= v[i].distance && v[left(i)].distance <= v[right(i)].distance)
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
				if (v[left(i)].distance <= v[i].distance)
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

		tuple_heap()
			: v(nullptr), n(0), count(0) {}

		tuple_heap(int dim)
			: v(new tuple[dim]), n(dim), count(0) {}

		~tuple_heap()
		{
			if (v != nullptr)
			{
				delete[] v;
			}
		}

		void print()
		{
			for (int i = 0; i < count; i++)
			{
				std::cout << "Key: " << v[i].key << "  Distance: " << v[i].distance << "\n";
			} 
		}

		void insert(tuple k)
		{
			if (count == n)
			{
				std::cout << "The HEAP if full\n\n";
				return;
			}

			v[count] = k;
			int i = count;
			count++;

			while (i != 0 && v[parent(i)].distance > v[i].distance)
			{
				swap(i, parent(i));
				i = parent(i);
			}

			return;
		}

		tuple& get_next()
		{
			return *v;
		}

		int extract_next()
		{
			if (count == 0)
			{
				std::cout << "ERROR: zero values in the heap";
				throw - 1;
			}

			int ret = v[0].key;

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

		bool decrease_distance(int k, int new_value)
		{
			for (int i = 0; i < count; i++)
			{
				if (v[i].key == k)
				{
					v[i].distance = new_value;

					while (i != 0 && v[i].distance < v[parent(i)].distance)
					{
						swap(i, parent(i));
						i = parent(i);
					}
					return true;
				}
			}
			return false;
		}
	};

	int V;
	adj_list E;

public:

	Graph()
		: V(0) {}

	Graph(int V)
		: V(V), E(adj_list(V)) {}

	~Graph() = default;

	void add(int a, int b, int weight)
	{
		return E.add_edge(a, b, weight);
	}

	void print()
	{
		edge* it;

		for (int i = 0; i < V; i++)
		{
			it = E[i];
			std::cout << it->key << "\n";
			while (it->ptr != nullptr)
			{
				it = it->ptr;
				std::cout << "\t---" << it->weight << "---> " << it->key << "\n";
			}
			std::cout << "\n\n";
		}

		return;
	}

private:

	void insertion_sort_distance(tuple* v, int n)
	{
		for (int i = 1; i < n; ++i)
		{
			int k = i;
			tuple tmp;
			while (v[k].distance < v[k - 1].distance && k>0)
			{
				tmp = v[k];
				v[k] = v[k - 1];
				v[k - 1] = tmp;
				--k;
			}
		}
		return;
	}

	void print_path(int source, int end, int* p)
	{
		if (end == source)
		{
			std::cout << source << "\t";
			return;
		}

		print_path(source, p[end], p);
		std::cout << "\t" << end;
		return;
	}

public:

	void Dijkstra_array(int source, int end)
	{
		if (source<0 || source>V || end<0 || end>V)
		{
			std::cout << "Index Error in Dijkstra!\n!";
			throw - 1;
		}

		int* d = new int[V];
		int* p = new int[V];
		tuple* Q = new tuple[V];
		for (int i = 0; i < V; i++)
		{
			d[i] = -1;
			p[i] = -1;
			Q[i].key = i;
			Q[i].distance = -1;
		}
		d[source] = 0;
		Q[source].distance = 0;

		
		int count = V;
		int exit;
		int min;
		tuple tmp;
		edge* it;
		while (count > 0)
		{
			exit = count;
			// ordino le tuple di Q in base alla distanza
			insertion_sort_distance(Q, count);
			//estraggo il più piccolo
			for (int i = 0; i < count; ++i)
			{
				if (Q[i].distance >= 0)
				{
					min = Q[i].key;
					tmp.key = Q[i].key;
					tmp.distance = Q[i].distance;
					for (int j = i; j < count - 1; j++)
					{
						Q[j].key = Q[j + 1].key;
						Q[j].distance = Q[j + 1].distance;
					}
					Q[count - 1].key = tmp.key;
					Q[count - 1].distance = tmp.distance;
					count -= 1;
					break;
				}
			}
			if (count == exit)
			{
				break;
			}

			// rilassamento
			it = E[min];
			while (it->ptr != nullptr)
			{
				it = it->ptr;
				if (d[it->key]<0 || d[it->key] > d[min] + it->weight)
				{
					d[it->key] = d[min] + it->weight;
					p[it->key] = min;
					for (int i = 0; i < V; i++)
					{
						if (Q[i].key == it->key)
						{
							Q[i].distance = d[it->key];
						}
					}
				}
			}
		}
		if (d[end] == -1)
		{
			std::cout << "No existing path between " << source << " and " << end << "\n\n";
		}
		else
		{
			std::cout << "Path: ";
			print_path(source, end, p);
			std::cout << "\n\nTotal distance: " << d[end] << "\n\n";
		}
		
		delete[] d;
		delete[] p;
		delete[] Q;
		return;
	}

	void Dijkstra_heap(int source, int end)
	{
		if (source<0 || source>V || end<0 || end>V)
		{
			std::cout << "Index Error in Dijkstra!\n!";
			throw - 1;
		}

		int* d = new int[V];
		int* p = new int[V];
		tuple_heap Q = tuple_heap(V);
		tuple_heap S = tuple_heap(V);
		for (int i = 0; i < V; i++)
		{
			if (i == source)
			{
				d[i] = 0;
				Q.insert(tuple(i, 0));
			}
			else
			{
				d[i] = std::numeric_limits<int>::max();
				p[i] = -1;
				Q.insert(tuple(i, std::numeric_limits<int>::max()));
			}
		}
		
		// fin qui giusto

		int min;
		tuple tmp;
		edge* it;
		while (Q.count > 0)
		{
			if (Q.get_next().distance == std::numeric_limits<int>::max())
			{
				break;
			}
			S.insert(Q.get_next());
			min = Q.extract_next();

			// rilassamento
			it = E[min];
			while (it->ptr != nullptr)
			{
				it = it->ptr;
				if (d[it->key]<0 || d[it->key] > d[min] + it->weight)
				{
					d[it->key] = d[min] + it->weight;
					if (!Q.decrease_distance(it->key, d[min] + it->weight))
					{
						S.decrease_distance(it->key, d[min] + it->weight);
					}
					p[it->key] = min;
				}
			}
		}
		
		if (d[end] == std::numeric_limits<int>::max())
		{
			std::cout << "No existing path between " << source << " and " << end << "\n\n";
		}
		else
		{
			std::cout << "Path: ";
			print_path(source, end, p);
			std::cout << "\n\nTotal distance: " << d[end] << "\n\n";
		}

		delete[] d;
		delete[] p;
		return;
	}

};
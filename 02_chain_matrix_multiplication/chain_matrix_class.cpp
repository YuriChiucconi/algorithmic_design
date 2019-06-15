#include <iostream>

#include <stdlib.h>  // rand()
#include <iomanip> // setw()
#include <math.h> // pow()

template <typename T>
class Matrix
{
private:
	
	int row;
	int col;

	T* v;
	// v[i][j] = v[i*col + j]

private:

	Matrix<T>* newSub(int row_b, int row_e, int col_b, int col_e)
	{
		Matrix<T>* ptr = new Matrix<T>(row_e - row_b + 1, col_e - col_b + 1);

		int j = 0;
		for (int i = 0; i < ptr->row*ptr->col; ++i)
		{
			if (i%ptr->col == 0 && i != 0) { ++j; }

			ptr->v[i] = this->v[(this->col)*(row_b + j) + col_b + i % (ptr->col)];
		}

		return ptr;
	}

	Matrix<T>* make_square(Matrix<T>* A11, Matrix<T>* A12, Matrix<T>* A21, Matrix<T>* A22)
	{
		int n = A11->row;

		Matrix<T>* A = new Matrix<T>(n * 2, n * 2);

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n * 2; ++j)
			{
				if (j < n)
				{
					A->v[i*n * 2 + j] = A11->v[i*n + j];
				}
				else
				{
					A->v[i*n * 2 + j] = A12->v[i*n + j - n];
				}
			}
		}
		for (int i = n; i < n * 2; ++i)
		{
			for (int j = 0; j < n * 2; ++j)
			{
				if (j < n)
				{
					A->v[i*n * 2 + j] = A21->v[(i - n)*n + j];
				}
				else
				{

					A->v[i*n * 2 + j] = A22->v[(i - n)*n + j - n];
				}
			}
		}

		return A;
	}

	Matrix<T>* strassen_aux(Matrix<T>* A, Matrix<T>* B)

	{
		int n = A->row;

		if (n <= 64)
		{
			return &((*A)*(*B));
		}


		Matrix<T>* A11 = A->newSub(0, n / 2 - 1, 0, n / 2 - 1);
		Matrix<T>* A12 = A->newSub(0, n / 2 - 1, n / 2, n - 1);
		Matrix<T>* A21 = A->newSub(n / 2, n - 1, 0, n / 2 - 1);
		Matrix<T>* A22 = A->newSub(n / 2, n - 1, n / 2, n - 1);


		Matrix<T>* B11 = B->newSub(0, n / 2 - 1, 0, n / 2 - 1);
		Matrix<T>* B12 = B->newSub(0, n / 2 - 1, n / 2, n - 1);
		Matrix<T>* B21 = B->newSub(n / 2, n - 1, 0, n / 2 - 1);
		Matrix<T>* B22 = B->newSub(n / 2, n - 1, n / 2, n - 1);

		Matrix<T>* S1 = &(*B12 - *B22);
		Matrix<T>* S2 = &(*A11 + *A12);
		Matrix<T>* S3 = &(*A21 + *A22);
		Matrix<T>* S4 = &(*B21 - *B11);
		Matrix<T>* S5 = &(*A11 + *A22);
		Matrix<T>* S6 = &(*B11 + *B22);
		Matrix<T>* S7 = &(*A12 - *A22);
		Matrix<T>* S8 = &(*B21 + *B22);
		Matrix<T>* S9 = &(*A11 - *A21);
		Matrix<T>* S10 = &(*B11 + *B12);

		Matrix<T>* P1 = strassen_aux(A11, S1);
		Matrix<T>* P2 = strassen_aux(S2, B22);
		Matrix<T>* P3 = strassen_aux(S3, B11);
		Matrix<T>* P4 = strassen_aux(A22, S4);
		Matrix<T>* P5 = strassen_aux(S5, S6);
		Matrix<T>* P6 = strassen_aux(S7, S8);
		Matrix<T>* P7 = strassen_aux(S9, S10);

		delete A11;
		delete A12;
		delete A21;
		delete A22;

		delete B11;
		delete B12;
		delete B21;
		delete B22;

		delete S1;
		delete S2;
		delete S3;
		delete S4;
		delete S5;
		delete S6;
		delete S7;
		delete S8;
		delete S9;
		delete S10;

		Matrix<T>* C11 = &(*P5 + *P4 - *P2 + *P6);
		Matrix<T>* C12 = &(*P1 + *P2);
		Matrix<T>* C21 = &(*P3 + *P4);
		Matrix<T>* C22 = &(*P5 + *P1 - *P3 - *P7);

		delete P1;
		delete P2;
		delete P3;
		delete P4;
		delete P5;
		delete P6;
		delete P7;

		Matrix<T>* C = make_square(C11, C12, C21, C22);

		delete C11;
		delete C12;
		delete C21;
		delete C22;

		return C;
	}

public:

	Matrix()
	{
		row = 0;
		col = 0;
		v = nullptr;
	}

	Matrix(int r, int c)
		: row(r), col(c)
	{
		v = new T[r*c];
	}

	~Matrix()
	{
		delete[] v;
	}

	Matrix(Matrix<T> && rhs)
		: row(rhs.row), col(rhs.col), v(rhs.v)
	{
		rhs.v = nullptr;
	}

	Matrix & operator=(Matrix<T> && rhs)
	{
		if (this != &rhs)
		{
			delete this->v;
			this->v = rhs.v;
			rhs.v = nullptr;
		}

		return *this;
	}

	Matrix(Matrix<T> const & rhs)
		: row(rhs.row), col(rhs.col), v(new T[rhs.row*rhs.col])
	{
		for (int i = 0; i < rhs.row*rhs.col; ++i)
		{
			this->v[i] = rhs.v[i];
		}
	}

	Matrix & operator=(Matrix<T> const & rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		T* tmp = new T[rhs.row*rhs.col];

		this->row = rhs.row;
		this->col = rhs.col;

		for (int i = 0; i < rhs.row*rhs.col; ++i)
		{
			tmp[i] = rhs.v[i];
		}
		delete this->v;
		this->v = tmp;
	}


	void zero()
	{
		for (int i = 0; i < this->row*this->col; ++i)
		{
			this->v[i] = 0;
		}
	}

	void id()
	{
		if (this->col != this->row) { return; }

		this->zero();
		for (int i = 0; i < this->row; ++i)
		{
			this->v[i*(this->col + 1)] = 1;
		}
		return;
	}

	void random(int min=-1, int max=1)
	{
	
		for (int i = 0; i < this->row*this->col; ++i)
		{
			this->v[i] = static_cast<T>((max - min) * ((double)rand() / (double)RAND_MAX) + min);
		}

	}

	void print()
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				std::cout << std::setw(10) << this->v[i*this->col + j] << " ";
			}
			std::cout << std::endl;
		}	
	}
	
	int r() { return this->row; }

	int c() { return this->col; }


	// OPERATORS

	T* operator[](int n)
	{
		if (n >= this->row) { throw - 1; }

		return &(this->v[n*this->col]);
	}

	Matrix<T>& operator+=(const Matrix<T>& b)
	{
		if (this->row != b.row || this->col != b.col) { throw - 1; }

		for (int i = 0; i < b.row * b.col; ++i)
		{
			this->v[i] += b.v[i];
		}

		return *this;
	}

	Matrix<T>& operator-=(const Matrix<T>& b)
	{
		if (this->row != b.row || this->col != b.col) { throw - 1; }

		for (int i = 0; i < b.row * b.col; ++i)
		{
			this->v[i] -= b.v[i];
		}

		return *this;
	}

	Matrix<T>& operator*=(const int n)
	{
		for (int i = 0; i < this->row * this->col; ++i)
		{
			this->v[i] *= n;
		}

		return *this;
	}

	friend Matrix<T>& operator+(const Matrix<T>& a, const Matrix<T>& b)
	{
		if (a.row != b.row || a.col != b.col) { throw - 1; }

		Matrix<T>* c = new Matrix<T>(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] + b.v[i];
		}

		return *c;  
	}

	friend Matrix<T>& operator-(const Matrix<T>& a, const Matrix<T>& b)
	{
		if (a.row != b.row || a.col != b.col) { throw - 1; }

		Matrix<T>* c = new Matrix<T>(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] - b.v[i];
		}

		return *c;
	}

	friend Matrix<T>& operator*(const Matrix<T>& a, const int n)
	{
		Matrix<T>* c = new Matrix<T>(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] * n;
		}

		return *c;
	}

	friend Matrix<T>& operator*(const int n, const Matrix<T>& a)
	{
		Matrix<T>* c = new Matrix<T>(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] * n;
		}

		return *c;
	}

	friend Matrix<T>& operator*(const Matrix<T>& a, const Matrix<T>& b)
	{
		// if (a.col != b.row) { throw - 1; }

		Matrix<T>* c = new Matrix<T>(a.row, b.col);
		(*c).zero();

		for (int i = 0; i < a.row; ++i)
		{
			for (int j = 0; j < b.col; ++j)
			{
				for (int k = 0; k < a.col; ++k)
				{
					(*c).v[i*(*c).col + j] += a.v[i*a.col + k] * b.v[k*b.col + j];
				}
			}
		}
		
		
		return *c;
	}

	bool operator==(Matrix<T>& b)
	{
		if (this->row != b.r()) 
		{ 
			std::cout << "Numero righe sbagliato";
			return false;
		}
		if (this->col != b.c()) 
		{
			std::cout << "Numero colonne sbagliato";
			return false;
		}

		for (int i = 0; i < b.r(); ++i)
		{
			for (int j = 0; j < b.c(); ++j)
			{
				if ((*this)[i][j] != b[i][j])
				{
					std::cout << "Valore i=" << i << ", j=" << j << " sbagliato.";
					return false;
				}
			}
		}

		return true;
	}

	// STRASSEN
	
	Matrix<T>& strassen(const Matrix<T>& b)
	{
		
		if (this->col != b.row) { throw - 1; }

		// "immergiamo" le matrici a e b in alto a sinistra in matrici di zeri A e B di dimensione 2^k

		int max = 0;
		if (this->row >= this->col && this->row >= b.col)
		{
			max = this->row;
		}
		else if (this->col >= this->row && this->col >= b.col)
		{
			max = this->col;
		}
		else
		{
			max = b.col;
		}

		int k = 0;
		while (max > pow(2, k))
		{
			++k;
		}

		Matrix<T>* A = new Matrix<T>(static_cast<int>(pow(2, k)), static_cast<int>(pow(2, k)));
		A->zero();

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				A->v[i*A->col + j] = this->v[i*(this->col) + j];
			}
		}

		Matrix<T>* B = new Matrix<T>(static_cast<int>(pow(2, k)), static_cast<int>(pow(2, k)));
		B->zero();

		for (int i = 0; i < b.row; ++i)
		{
			for (int j = 0; j < b.col; ++j)
			{
				B->v[i*B->col + j] = b.v[i*b.col + j];
			}
		}


		Matrix<T>* C_0 = strassen_aux(A, B);
		delete A;
		delete B;
		Matrix<T>* C = C_0->newSub(0, this->row - 1, 0, b.col - 1);
		delete C_0;

		return *C;
	}

};

template <typename T>
class ChainMatrix
{
private:

	int dim;
	Matrix<T>* chain;

	int count;

private:

	ChainMatrix<T>* newSubChain(const ChainMatrix<T>* M, int b, int e)
	{
		if (b<0 || e>count || b>e) { throw - 1; }

		
		ChainMatrix<T>* sub = new ChainMatrix<T>(e-b);
		

		for (int i = b; i < e; ++i)
		{
			sub->add(M->chain[i]);
		}

		sub->count = e - b;
		return sub;
	}

	Matrix<T>* multiply_aux(ChainMatrix<T>* C)
	{
		if (C->count == 1)
		{
			return &(C->chain[0]);
		}
		if (C->count == 2)
		{
			return &(C->chain[0] * C->chain[1]);
		}

		// Creo la matrice m

		Matrix<int>* m = new Matrix<int>(C->count, C->count);
		m->zero();

		for (int d = 1; d < C->count; ++d)
		{
			for (int i = 0; i < C->count - d; ++i)
			{
				int* k_s = new int[d];

				int* min = new int;
				int* s = new int;


				for (int k = i; k < i + d; ++k)
				{
					k_s[k - i] = (*m)[i][k] + (*m)[k + 1][i + d] + C->chain[i].r()*C->chain[k].c()*C->chain[i + d].c();

					if (k == i || k_s[k - i] < *min)
					{
						*min = k_s[k - i];
						*s = k;
					}
				}

				(*m)[i][i + d] = *min;
				(*m)[i + d][i] = *s;

				delete s;
				delete min;
				delete[] k_s;
			}
		}

		
		ChainMatrix<T>* C1 = this->newSubChain(C, 0, (*m)[C->count - 1][0] + 1);
		ChainMatrix<T>* C2 = this->newSubChain(C, (*m)[C->count - 1][0] + 1, C->count);


		Matrix<T>* ret = new Matrix<T>;
		Matrix<T>* m1 = multiply_aux(C1);
		Matrix<T>* m2 = multiply_aux(C2);
		ret = &(*(m1) * *(m2));

		delete m;
		delete C1;
		delete C2;

		return ret;
	}

	Matrix<T>* standard_multiply_aux(ChainMatrix<T>* C)
	{
		if (C->count == 1)
		{
			return &C->chain[0];
		}
		else
		{
			return &(C->chain[0] * *standard_multiply_aux(C->newSubChain(C, 1, C->count)));
		}
		
	}

public:

	ChainMatrix()
		: dim(0), chain(nullptr), count(0) {}

	ChainMatrix(int n)
		: dim(n)
	{
		chain = new Matrix<T>[dim];
		count = 0;
	}

	~ChainMatrix()
	{
		delete[] chain;
	}

	void add(Matrix<T>& M)
	{
		if (count < dim)
		{
			if (count != 0 && chain[count - 1].c() != M.r())
			{
				std::cout << "\n\nWrong dimensions!\nImpossible to add the matrix\n\n";
				return;
			}

			chain[count] = M;
			++count;
			return;
		}
		else
		{
			std::cout << "\nThe chain is full!\nImpossible to add the matrix\n\n";
			return;
		}
	}

	Matrix<T>& multiply()
	{
		return *multiply_aux(this);
	}

	Matrix<T>& standard_multiply()
	{
		return *standard_multiply_aux(this);
	}
};
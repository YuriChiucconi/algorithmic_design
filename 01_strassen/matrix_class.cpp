#include <iostream>

#include <stdlib.h>  // rand()
#include <iomanip> // setw()
#include <math.h> // pow()

class Matrix
{
private:

	int row;
	int col;

	double* v;
	// v[i][j] = v[i*col + j]

private:

	Matrix* newSub(int row_b, int row_e, int col_b, int col_e)
	{
		Matrix* ptr = new Matrix(row_e - row_b + 1, col_e - col_b + 1);

		int j = 0;
		for (int i = 0; i < ptr->row*ptr->col; ++i)
		{
			if (i%ptr->col == 0 && i != 0) { ++j; }

			ptr->v[i] = this->v[(this->col)*(row_b + j) + col_b + i % (ptr->col)];
		}

		return ptr;
	}

	Matrix* make_square(Matrix* A11, Matrix* A12, Matrix* A21, Matrix* A22)
	{
		int n = A11->row;

		Matrix* A = new Matrix(n * 2, n * 2);

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

	Matrix* strassen_aux(Matrix* A, Matrix* B)

	{
		int n = A->row;

		if (n <= 64)
		{
			return &((*A)*(*B));
		}

		// std::cout << "A\n";
		// A->print();
		// std::cout << "\n\nB\n";
		// B->print();
		// std::cout << "\n\nA11\n";

		Matrix* A11 = A->newSub(0, n / 2 - 1, 0, n / 2 - 1);
		Matrix* A12 = A->newSub(0, n / 2 - 1, n / 2, n - 1);
		Matrix* A21 = A->newSub(n / 2, n - 1, 0, n / 2 - 1);
		Matrix* A22 = A->newSub(n / 2, n - 1, n / 2, n - 1);


		// A11->print();
		// std::cout << "\n\nA12\n";
		// A12->print();
		// std::cout << "\n\nA21\n";
		// A21->print();
		// std::cout << "\n\nA22\n";
		// A22->print();
		// std::cout << "\n\nB11\n";

		Matrix* B11 = B->newSub(0, n / 2 - 1, 0, n / 2 - 1);
		Matrix* B12 = B->newSub(0, n / 2 - 1, n / 2, n - 1);
		Matrix* B21 = B->newSub(n / 2, n - 1, 0, n / 2 - 1);
		Matrix* B22 = B->newSub(n / 2, n - 1, n / 2, n - 1);

		// B11->print();
		// std::cout << "\n\nB12\n";
		// B12->print();
		// std::cout << "\n\nB21\n";
		// B21->print();
		// std::cout << "\n\nB22\n";
		// B22->print();
		// std::cout << "\n\n\n";

		Matrix* S1 = &(*B12 - *B22);
		Matrix* S2 = &(*A11 + *A12);
		Matrix* S3 = &(*A21 + *A22);
		Matrix* S4 = &(*B21 - *B11);
		Matrix* S5 = &(*A11 + *A22);
		Matrix* S6 = &(*B11 + *B22);
		Matrix* S7 = &(*A12 - *A22);
		Matrix* S8 = &(*B21 + *B22);
		Matrix* S9 = &(*A11 - *A21);
		Matrix* S10 = &(*B11 + *B12);

		Matrix* P1 = strassen_aux(A11, S1);
		Matrix* P2 = strassen_aux(S2, B22);
		Matrix* P3 = strassen_aux(S3, B11);
		Matrix* P4 = strassen_aux(A22, S4);
		Matrix* P5 = strassen_aux(S5, S6);
		Matrix* P6 = strassen_aux(S7, S8);
		Matrix* P7 = strassen_aux(S9, S10);

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

		Matrix* C11 = &(*P5 + *P4 - *P2 + *P6);
		Matrix* C12 = &(*P1 + *P2);
		Matrix* C21 = &(*P3 + *P4);
		Matrix* C22 = &(*P5 + *P1 - *P3 - *P7);

		delete P1;
		delete P2;
		delete P3;
		delete P4;
		delete P5;
		delete P6;
		delete P7;

		Matrix* C = make_square(C11, C12, C21, C22);

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
		v = new double[r*c];
	}

	~Matrix()
	{
		delete[] v;
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
			this->v[i] = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
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

	double* operator[](int n)
	{
		if (n >= this->row) { throw - 1; }

		return &(this->v[n*this->col]);
	}

	Matrix& operator+=(const Matrix& b)
	{
		if (this->row != b.row || this->col != b.col) { throw - 1; }

		for (int i = 0; i < b.row * b.col; ++i)
		{
			this->v[i] += b.v[i];
		}

		return *this;
	}

	Matrix& operator-=(const Matrix& b)
	{
		if (this->row != b.row || this->col != b.col) { throw - 1; }

		for (int i = 0; i < b.row * b.col; ++i)
		{
			this->v[i] -= b.v[i];
		}

		return *this;
	}

	Matrix& operator*=(const int n)
	{
		for (int i = 0; i < this->row * this->col; ++i)
		{
			this->v[i] *= n;
		}

		return *this;
	}

	friend Matrix& operator+(const Matrix& a, const Matrix& b)
	{
		if (a.row != b.row || a.col != b.col) { throw - 1; }

		Matrix* c = new Matrix(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] + b.v[i];
		}

		return *c;  
	}

	friend Matrix& operator-(const Matrix& a, const Matrix& b)
	{
		if (a.row != b.row || a.col != b.col) { throw - 1; }

		Matrix* c = new Matrix(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] - b.v[i];
		}

		return *c;
	}

	friend Matrix& operator*(const Matrix& a, const int n)
	{
		Matrix* c = new Matrix(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] * n;
		}

		return *c;
	}

	friend Matrix& operator*(const int n, const Matrix& a)
	{
		Matrix* c = new Matrix(a.row, a.col);

		for (int i = 0; i < a.row * a.col; ++i)
		{
			(*c).v[i] = a.v[i] * n;
		}

		return *c;
	}

	friend Matrix& operator*(const Matrix& a, const Matrix& b)
	{
		// if (a.col != b.row) { throw - 1; }

		Matrix* c = new Matrix(a.row, b.col);
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

	// STRASSEN
	
	Matrix& strassen(const Matrix& b)
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

		Matrix* A = new Matrix(static_cast<int>(pow(2, k)), static_cast<int>(pow(2, k)));
		A->zero();

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				A->v[i*A->col + j] = this->v[i*(this->col) + j];
			}
		}

		Matrix* B = new Matrix(static_cast<int>(pow(2, k)), static_cast<int>(pow(2, k)));
		B->zero();

		for (int i = 0; i < b.row; ++i)
		{
			for (int j = 0; j < b.col; ++j)
			{
				B->v[i*B->col + j] = b.v[i*b.col + j];
			}
		}


		Matrix* C_0 = strassen_aux(A, B);
		delete A;
		delete B;
		Matrix* C = C_0->newSub(0, this->row - 1, 0, b.col - 1);
		delete C_0;

		return *C;
	}

	
};

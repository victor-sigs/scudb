#include "p0_starter.h"

template <typename T>
class Matrix {
protected:
	Matrix(int rows, int cols) {
		rows_ = rows;
		cols_ = cols;
		linear_ = new T[rows * cols];
		memset(linear_, 0, sizeof(T) * rows * cols);
	}
	int rows_;
	int cols_;

	T* linear_;

public:
	virtual int GetRowCount() const = 0;
	virtual int GetColumnCount() const = 0;
	virtual T GetElement(int i, int j) const = 0;
	virtual void SetElement(int i, int j, T val) = 0;
	virtual void FillFrom(const std::vector<T>& source) = 0;
	virtual ~Matrix() {
		delete[] linear_;
	}
};


template <typename T>
class RowMatrix : public Matrix<T>
{
public:
	RowMatrix(int rows, int cols) : Matrix<T>(rows, cols) {
		data_ = new T * [rows];
		for (int i = 0; i < rows; i++) {
			data_[i] = &this->linear_[i * cols];
		}
	}
	int GetRowCount() const override { 
		return this->rows_; 
	}
	int GetColumnCount() const override { 
		return this->cols_; 
	}
	T GetElement(int i, int j) const override { 
		return data_[i][j]; 
	}
	void SetElement(int i, int j, T val) override {
		data_[i][j] = val;
	}
	void FillFrom(const std::vector<T>& source) override {
		for (int i = 0; i < this->rows_; i++) {
			for (int j = 0; j < this->cols_; j++) {
				data_[i][j] = source[i * this->cols_ + j];
			}
		}
	}
	~RowMatrix()
	{
		delete[] data_;
	}
private:
	T** data_;
};


template <typename T>
class RowMatrixOperations {
public:
	static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB) {

		if (matrixA->GetRowCount() != matrixB->GetRowCount() || matrixA->GetColumnCount() != matrixB->GetColumnCount()) {
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}
		int rows = matrixA->GetRowCount();
		int cols = matrixA->GetColumnCount();
		std::unique_ptr<RowMatrix<T>> matrixAaddB(new RowMatrix<T>(rows, cols));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				matrixAaddB->SetElement(i, j, matrixA->GetElement(i, j) + matrixB->GetElement(i, j));
			}
		}
		return matrixAaddB;
	}

	static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB) {
		if (matrixA->GetColumnCount() != matrixB->GetRowCount()) {
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}

		int rows = matrixA->GetRowCount();
		int cols = matrixB->GetColumnCount();
		std::unique_ptr<RowMatrix<T>> matrixAmulB(new RowMatrix<T>(rows, cols));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				for (int k = 0; k < matrixA->GetColumnCount(); k++) {
					T tmp = matrixAmulB->GetElement(i, j);
					matrixAmulB->SetElement(i, j, tmp + matrixA->GetElement(i, k) * matrixB->GetElement(k, j));
				}
			}
		}
		return matrixAmulB;
	}

	static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB,
		const RowMatrix<T>* matrixC) {
		std::unique_ptr<RowMatrix<T>> tmp = Multiply(matrixA, matrixB);
		if (tmp.get() == nullptr) {
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}
		int rows = matrixA->GetRowCount();
		int cols = matrixA->GetColumnCount();
		std::unique_ptr<RowMatrix<int>> matrixAgemmB(new RowMatrix<T>(rows, cols));
		for (int i = 0; i < tmp->GetRowCount(); i++)
		{
			for (int j = 0; j < tmp->GetColumnCount(); j++)
			{

				matrixAgemmB->SetElement(i, j, tmp->GetElement(i, j) + matrixC->GetElement(i, j));

			}
		}

		return matrixAgemmB;
	}
};

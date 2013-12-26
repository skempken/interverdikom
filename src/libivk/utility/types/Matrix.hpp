#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

using std::vector;

template<typename T> class Matrix {
private:
	int height;

	int width;

	vector< vector<T> > contents;

public:
	Matrix<T>(int height, int width) :
		height(height), width(width) {
		contents.resize(height, vector<T>(width, T()));
	}

	virtual ~Matrix<T>() {
	}
	

	Matrix<T> & operator=(const Matrix<T> &rhs) {
		if (this != &rhs) {
			height = rhs.height;
			width = rhs.width;
			contents = rhs.contents;
		}

		return *this;
	}

	Matrix<T>(const Matrix<T> &other) {
		*this = other;
	}
	
	vector<T> & operator[](const int &index) {
		return contents[index];
	}
};

#endif /*MATRIX_H_*/

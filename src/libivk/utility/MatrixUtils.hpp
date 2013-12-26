#ifndef MATRIXUTILS_H_
#define MATRIXUTILS_H_

#include <algorithm>
#include <cassert>

#include <real.hpp>

namespace ivk
{

/**
 * Template classes:
 * M : Matrix type
 * V : Vector type
 * E : Element type
 *
 * The constructors
 * M(Lb1, Ub1, Lb2, Ub2)
 * V(Lb, Ub)
 * must be defined.
 *
 * The functions Lb(M,int), Ub(M, int), Lb(V), Ub(V) must be defined.
 *
 * Luckily, this is the case for the C-XSC matrix types. :-)
 */
template <class M, class V, class E>
class MatrixUtils
{
public:
	/// Transposes the given matrix.
	static M transpose(const M &A)
	{
		M B(Lb(A,2), Ub(A,2), Lb(A,1), Ub(A,1));
		for(int r = Lb(A,1); r<=Ub(A,1); ++r)
		{
			for(int c = Lb(A,2); c <=Ub(A,2); ++c)
			{
				B[c][r] = A[r][c];
			}
		}
		return B;
	}

	/// Returns sum of all matrix entries.
	static E sum(const M &a)
	{
		E sum = (E) 0;
		for(int i = Lb(a,1); i<=Ub(a,1); ++i)
			for(int j = Lb(a,2); j<=Ub(a,2); ++j)
				sum += a[i][j];
		return sum;
	}

	/// Returns sum of all vector entries.
	static E sum(const V &a)
	{
		E sum = (E) 0;
		for(int i = Lb(a); i<=Ub(a); ++i)
			sum += a[i];
		return sum;
	}

	static M eye(int size) {
		M result(1, size, 1, size);

		for (int i = Lb(result, 1); i <= Ub(result, 1); i++) {
			for (int j = Lb(result, 2); j <= Ub(result, 2); j++) {
				result[i][j] = (i == j);
			}
		}

		return result;
	}

	/// Returns sum vector of rows.
	static V sumRows(const M &a)
	{
		V sum(Lb(a,1), Ub(a,1));
		for(int i = Lb(a,1); i<=Ub(a,1); ++i)
			sum[i] = (E) 0;
		for(int i = Lb(a,1); i<=Ub(a,1); ++i)
			for(int j = Lb(a,2); j<=Ub(a,2); ++j)
				sum[i] += a[i][j];
		return sum;
	}

	static bool containsNAN(const M & matrix) {
		for (int i = Lb(matrix, 1); i <= Ub(matrix, 1); i++) {
			for (int j = Lb(matrix, 2); j <= Ub(matrix, 2); j++) {
				if ((matrix[i][j] == cxsc::QuietNaN) || (matrix[i][j] == cxsc::SignalingNaN)
						|| (matrix[i][j] == cxsc::Infinity)) {
					return true;
				}
			}
		}

		return false;
	}

	static E maxElement(const M &matrix) {
		E result = matrix[1][1];
		for (int i = Lb(matrix, 1); i <= Ub(matrix, 1); i++) {
			for (int j = Lb(matrix, 2); j <= Ub(matrix, 2); j++) {
				if (matrix[i][j] > result) {
					result = matrix[i][j];
				}
			}
		}

		return result;
	}

	static E minElement(const M &matrix) {
		E result = matrix[1][1];
		for (int i = Lb(matrix, 1); i <= Ub(matrix, 1); i++) {
			for (int j = Lb(matrix, 2); j <= Ub(matrix, 2); j++) {
				if (matrix[i][j] < result) {
					result = matrix[i][j];
				}
			}
		}

		return result;
	}

	static int minIndex(const V &vector) {
		int result = Lb(vector);
		E minElement = vector[Lb(vector)];
		for (int i = Lb(vector) + 1; i <= Ub(vector); i++) {
			if (vector[i] < minElement) {
				minElement = vector[i];
				result = i;
			}
		}

		return result;
	}

	/// Returns sum vector of columns.
	static V sumCols(const M &a)
	{
		V sum(Lb(a,2), Ub(a,2));
		for(int j = Lb(a,2); j<=Ub(a,2); ++j)
			sum[j] = (E) 0;
		for(int i = Lb(a,1); i<=Ub(a,1); ++i)
			for(int j = Lb(a,2); j<=Ub(a,2); ++j)
				sum[j] += a[i][j];
		return sum;
	}
	
	/// Removes specifies row.
	static M rmRow(const M &a, const int row)
	{
		assert(row>=Lb(a,1));
		assert(row<=Ub(a,1));
		M tmp(Lb(a,1), Ub(a,1)-1, Lb(a,2), Ub(a,2));
		int rowCount = Lb(a,1);
		for(int i = Lb(a,1); i<=Ub(a,1); ++i)
		{
			if(i!=row)
			{
				for(int j=Lb(a,2); j<=Ub(a,2); ++j)
					tmp[rowCount][j] = a[i][j];
				rowCount++;
			}
		}
		return tmp;
	}

	static E norm2(const V & vector) {
		E result;
		result = 0;
		for (int i = Lb(vector); i <= Ub(vector); i++) {
			result += vector[i] * vector[i];
		}
		return sqrt(result);
	}

	/// Removes specified column.
	static M rmCol(const M &a, const int col)
	{
		assert(col>=Lb(a,2));
		assert(col<=Ub(a,2));
		M tmp(Lb(a,1), Ub(a,1), Lb(a,2), Ub(a,2)-1);
		int colCount = Lb(a,2);
		for(int j = Lb(a,2); j<=Ub(a,2); ++j)
		{
			if(j!=col)
			{
				for(int i=Lb(a,1); i<=Ub(a,1); ++i)
					tmp[i][colCount] = a[i][j];
				colCount++;
			}
		}
		return tmp;
	};

	/// Creates a circular matrix from the given vector.
	static M circular(const V &vector)
	{
		M ret(Lb(vector), Ub(vector), Lb(vector), Ub(vector));
		for(int i = Lb(vector); i<=Ub(vector); ++i)
		{
			for(int j = Lb(vector); j<=Ub(vector); ++j)
			{
				int shiftedJ = j + (i-Lb(vector));
				if(shiftedJ > Ub(vector)) shiftedJ -= VecLen(vector);
				ret[i][shiftedJ] = vector[j];
			}
		}
		return ret;
	}

	/// Evaluates the determinant according to Laplace.
	static E detLaplace(const M &matrix)
	{
		E det = (E) 0;
		assert(Lb(matrix,1) == Lb(matrix,2));
		assert(Ub(matrix,1) == Ub(matrix,2));
		const int size = Ub(matrix,1) - Lb(matrix,1) +1;

		switch(size)
		{
		case 1:
			det = matrix[Lb(matrix,1)][Lb(matrix,2)];
			break;
		case 2:
			det = matrix[Lb(matrix,1)][Lb(matrix,2)] * matrix[Lb(matrix,1)+1][Lb(matrix,2)+1] -
				matrix[Lb(matrix,1)][Lb(matrix,2)+1] * matrix[Lb(matrix,1)+1][Lb(matrix,2)];
			break;
		default:
			// Entwicklung nach der 1. Spalte
	        for (int k = Lb(matrix,1); k <= Ub(matrix,1); k++)
	        {
	        	M tmp = rmRow(rmCol(matrix,1), k);

	            if ((k-Lb(matrix,1)) % 2 == 0)
	                det += matrix[k][Lb(matrix,2)] * detLaplace(tmp);
	            else
	                det -= matrix[k][Lb(matrix,2)] * detLaplace(tmp);
	        }
	        break;
		}
	    return det;
	}

	static V diag(const M &matrix)
	{
		assert(Lb(matrix,1) == Lb(matrix,2));
		assert(Ub(matrix,1) == Ub(matrix,2));

		V ret(Lb(matrix,1), Ub(matrix,1));
		for(int i = Lb(matrix,1); i<=Ub(matrix,1); ++i)
			ret[i] = matrix[i][i];

		return ret;
	}

	/**
	 * Simple convolution of two vectors.
	 */
	static V conv(const V &v1, const V &v2)
	{
		const int lowerBound = Lb(v1)+Lb(v2);
		const int upperBound = Ub(v1)+Ub(v2);
		V ret(lowerBound, upperBound);
		for(int i = lowerBound; i<=upperBound; ++i)
			ret[i] = (E) 0.0;
		for(int i = Lb(v1); i<=Ub(v1); ++i)
			for(int j = Lb(v2); j<=Ub(v2); ++j)
				ret[i+j] += v1[i] * v2[j];
		return ret;
	}
	
	static bool isZero(const M & m) {
		for (int i = Lb(m, 1); i <= Ub(m, 1); i++) {
			for (int j = Lb(m, 2); j <= Ub(m, 2); j++) {
				if (m[i][j] != 0) {
					return false;
				}
			}
		}
		
		return true;
	}

};

}

#endif /*MATRIXUTILS_H_*/

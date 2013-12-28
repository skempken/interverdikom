#include "Determinant.h"

#include <iostream>

using std::cout;
using std::endl;

namespace ivk {

/*
 * Evaluates polynomial determinant according to Laplace.
 */
IPolynomial Determinant::laplace(IPolynomial** polynommatrix, int m)
{
    IPolynomial ergebnis(0);
    ergebnis[0] = interval(0.0,0.0);

    if (m == 1)
        ergebnis = polynommatrix[0][0];
    else if (m == 2)
        ergebnis = polynommatrix[0][0] * polynommatrix[1][1] - polynommatrix[0][1] * polynommatrix[1][0];
    else
    {
        IPolynomial ** hilfspolynommatrix = new IPolynomial*[m-1];
        for (int i = 0; i < m-1; i++)
        {
            hilfspolynommatrix[i] = new IPolynomial[m-1];

        }


        // Entwicklung nach der 1. Spalte
        for (int k = 0; k < m; k++)
        {
           // hilfspolynommatrix = Streichungsmatrix 1. Spalte, k. Zeile
            for (int i = 0; i < m-1; i++)
                 for (int j = 0; j < m-1; j++)
                 {
                     if (i < k)
                     {
                          hilfspolynommatrix[i][j] = polynommatrix[i][j+1];
                     }
                     else
                     {
                          hilfspolynommatrix[i][j] = polynommatrix[i+1][j+1];
                     }
                 }

            if (k % 2 == 0)
                ergebnis += polynommatrix[k][0] * laplace(hilfspolynommatrix, m-1);
            else
                ergebnis -= polynommatrix[k][0] * laplace(hilfspolynommatrix, m-1);
        }

        for (int i = 0; i < m-1; i++)
            delete[] hilfspolynommatrix[i];

        delete[] hilfspolynommatrix;
    }
    //cout << "m="<<m << endl << ergebnis << endl;
    return ergebnis;
}

/*
 * Evaluates the determinant using Faddeev's method.
 * cf: Beaufils / Luther, "Algorithmes", Sybex 1985,  pp. 96-100.
 */
IPolynomial Determinant::faddeev(IPolynomial** polynommatrix, const int &m)
{
	// Matrices A,B
	IPolynomial SS;
	IPolynomial* P = new IPolynomial[m];
	IPolynomial* B1 = new IPolynomial[m];
	IPolynomial** A = new IPolynomial*[m];
	IPolynomial** B = new IPolynomial*[m];

	// A = M, B = M
	for (int i = 0; i<m; i++)
	{
		A[i] = new IPolynomial[m];
		B[i] = new IPolynomial[m];
		for(int j = 0; j<m; j++)
		{
			A[i][j] = IPolynomial(polynommatrix[i][j]);
			B[i][j] = IPolynomial(polynommatrix[i][j]);
		}
	}

	for(int k = 0; k<m; k++)
	{
		// Trace of Matrix B
		IPolynomial tr(m);
		for(int i = 0; i<m; i++)
			tr[i] = interval(0.0,0.0);

		for(int i = 0; i<m; i++)
			tr = tr + B[i][i];

		// Polynomial P
		P[k] = IPolynomial(tr.degree());
		for(int i = 0; i<=tr.degree(); i++)
		{
			P[k][i] = (tr[i] / (k+1));
		}

		// Matrix B
		for(int i = 0; i<m; i++)
		{
			B[i][i] = B[i][i] - P[k];
		}

		if(k<(m-1))
		{
			// Matrix A(k+1)
			for(int j = 0; j<m; j++)
			{
				for(int i=0; i<m; i++)
				{
					B1[i] = B[i][j];
				}
				for(int i=0; i<m; i++)
				{
					SS = 0;
					for(int l=0; l<m; l++)
					{
						SS = SS + A[i][l] * B1[l];
					}
					B[i][j] = SS;
				}
			}
		}
	}
	return P[m-1];
}

}

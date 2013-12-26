#ifndef MATRIXACCU_H_
#define MATRIXACCU_H_

#include <imatrix.hpp>
#include <rmatrix.hpp>
#include <idot.hpp>
#include <dot.hpp>

using namespace cxsc;

/**
 * --- Shitty C-XSC bugfix ---
 * If you are annoyed by this, walk to Wuppertal and burn the Uni to the ground.
 */
namespace cxsc {
	interval rnd(const idotprecision &a) throw();
	real rnd (const dotprecision& d, rndtype type) throw();
}

// --- End of shitty bugfix ---

namespace ivk
{

template <class P, class M>
class MatrixAccu
{
public:
	
	MatrixAccu(int lb1, int ub1, int lb2, int ub2)
	: m_lb1(lb1), m_ub1(ub1), m_lb2(lb2), m_ub2(ub2)
	{
		size1 = ub1 - lb1 + 1;
		size2 = ub2 - lb2 + 1;
		// primitive range-checking
		assert(size1 > 0);
		assert(size2 > 0);
		m_accu = new P*[size1];
		for(int i = 0; i<size1; ++i)
			m_accu[i] = new P[size2]; 
		// clear
		for(int i = 0; i<size1; ++i)
			for(int j = 0; j<size2; ++j)
				m_accu[i][j] = 0.0;
				
	}
	virtual ~MatrixAccu()
	{
		for(int i = 0; i<size1; ++i)
			delete[] m_accu[i];
		delete[] m_accu;
	}
	
	void accumulate(const M &op1, const M &op2)
	{
		// Multiply matrices
		for(int i = Lb(op1,1); i<=Ub(op1,1); ++i)
		{
			for(int j = Lb(op2,1); j<=Ub(op2,1); ++j)
			{
				P& dotaccu = m_accu[i-m_lb1][j-m_lb2];
				cxsc::accumulate(dotaccu, op1[i], op2[Col(j)]);
			}
		}
	}
	
	M rnd()
	{
		M res(m_lb1, m_ub1, m_lb2, m_ub2);
		for(int i = m_lb1; i<=m_ub1; ++i)
		{
			for(int j = m_lb2; j<=m_ub2; ++j)
			{
				P& dotaccu = m_accu[i-m_lb1][j-m_lb2];
				res[i][j] = cxsc::rnd(dotaccu);
			}
		}
		return res;
	}

private:
	int m_lb1;
	int m_ub1;
	int m_lb2;
	int m_ub2;
	int size1;
	int size2;
	P** m_accu;
};

typedef MatrixAccu<dotprecision, rmatrix>  rmatrixaccu;
typedef MatrixAccu<idotprecision, imatrix> imatrixaccu;


}

#endif /*MATRIXACCU_H_*/

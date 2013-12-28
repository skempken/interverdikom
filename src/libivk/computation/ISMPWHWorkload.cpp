#include "ISMPWHWorkload.h"

#include "utility/solvers/ILinSys.hpp"
#include "utility/IMatrixUtils.h"
#include <idot.hpp>
#include <l_imatrix.hpp>
#include <l_ivector.hpp>

#include "utility/Logging.hpp"

namespace ivk
{

// Static string constants.
const char * ISMPWHWorkload::PARAM_UPTO = "upTo";

ISMPWHWorkload::ISMPWHWorkload(const ISMPWHFactors *data, const ComputationParameters &parameters)
: AbstractComputation<ISMPWHFactors, IWorkloadVector>(data, parameters)
{
	setParameters(parameters);
}

ISMPWHWorkload::~ISMPWHWorkload()
{
}

void ISMPWHWorkload::setParameters(const ComputationParameters &parameters)
{
	setUpTo(parameters.getInt(PARAM_UPTO));
}

void ISMPWHWorkload::setUpTo(const int upTo)
{
	this->m_upTo = upTo;
}

int ISMPWHWorkload::getUpTo()
{
	return this->m_upTo;
}

IWorkloadVector* ISMPWHWorkload::compute()
{
	IMatrixPolynomial l_int = this->m_ptrData->getIdleDistributions();
	IMatrixPolynomial v_int = this->m_ptrData->getPhaseDistributions();
	
	const int h = v_int.degree();
	const int m = Ub(l_int[0],1)-Lb(l_int[0],1)+1;
	
	ivector ret(0, this->getUpTo());
	
	// Both SMP/G/1 and GI/G/1
	
	// Compute V(1)
	const imatrix v1 = v_int.sum();
	Logging::log(Logging::Debug, "v1", v1);
	
	const imatrix I = IMatrixUtils::identity(1,m);
	
	// E(N) = (I-V(1))^-1
    const ivector e_von_n = IMatrixUtils::sumRows(IMatrixUtils::invert(I-v1));
    Logging::log(Logging::Debug, "E(N)", e_von_n);
    
    // l_i = sum_i l_i l_ij, l_ij = sum_k l_ij(k)
    ivector l_i = computeLI(l_int);
    Logging::log(Logging::Debug, "l_i", l_i);
    
    // sum_i l_i E(N_i)
    idotprecision nenner(0.0);
    for ( int i = 1; i <= m; i++ )
    	accumulate(nenner, l_i[i], e_von_n[i]);
        
	imatrix e_von_n_i_w_i(0, getUpTo(), 1,m);
	const imatrix inverse = IMatrixUtils::invert(I-v_int[0]);
	Logging::log(Logging::Debug, "(I-V[0])^-1", inverse);
    e_von_n_i_w_i[0] = IMatrixUtils::sumRows(inverse);
    idotprecision zaehler;
    zaehler = 0.0;

    for ( int i = 1; i <= m; i++ )
    	accumulate(zaehler, l_i[i], e_von_n_i_w_i[0][i]);
    

    /* GI/G/1 optimization */
	if(m == 1) // GI/G/1 case
	{
	    ret[0] = (I-v1)[1][1] / (I-v_int[0])[1][1]; 
	}
	else // SMP/G/1 case
	{
	    ret[0] = rnd(zaehler) / rnd(nenner);
	}
	
	int minimum = 0;
	for(int n = 1; n<=getUpTo(); ++n)
    {
       // Berechne w(n)
        minimum = std::min<int>( h, n );
        
        ivector rechte_seite(1,m);
        for ( int i = 1; i <= m; i++ )
           rechte_seite[i] = 0.0;

        for ( int k = 1; k <= minimum; k++ )
           rechte_seite += v_int[k] * e_von_n_i_w_i[n-k];
        
        e_von_n_i_w_i[n] = inverse * rechte_seite;
                                
        zaehler = 0.0;

        for ( int i = 1; i <= m; i++ )
        	accumulate(zaehler, l_i[i], e_von_n_i_w_i[n][i]);
		ret[n] = rnd(zaehler) / rnd(nenner);
    }
	
	Logging::log(Logging::Debug, "Workload vector", ret);
	
	return new IWorkloadVector(ret);
}

ivector ISMPWHWorkload::computeLI( IMatrixPolynomial ll)
{
	const int m = Ub(ll[0],1) - Lb(ll[0],1) +1;
    ivector rechte_seite(1, m ), ergebnis(1, m );
    imatrix linke_seite( 1, m, 1, m ), inverse(1, m, 1, m );
	imatrix l = ll.sum();
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == j)
                linke_seite[i][j] = l[i][j] - 1.0;
            else
                linke_seite[i][j] = l[j][i];
        }
        
    }
    for(int i = 1; i<=m ; ++i)
    	linke_seite[m][i] = 1.0;

    inverse = IMatrixUtils::invert(linke_seite);
    for ( int i = 1; i < m; i++ ) rechte_seite[i] = 0.0;
    rechte_seite[m] = 1.0;
    ergebnis = inverse * rechte_seite;

    return ergebnis;

}

}

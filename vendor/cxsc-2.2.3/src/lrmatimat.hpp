/*
**  CXSC is a C++ library for eXtended Scientific Computing (V 2.2.3)
**
**  Copyright (C) 1990-2000 Institut fuer Angewandte Mathematik,
**                          Universitaet Karlsruhe, Germany
**            (C) 2000-2008 Wiss. Rechnen/Softwaretechnologie
**                          Universitaet Wuppertal, Germany   
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Library General Public
**  License as published by the Free Software Foundation; either
**  version 2 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public
**  License along with this library; if not, write to the Free
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVS $Id: lrmatimat.hpp,v 1.13 2008/01/23 08:39:31 cxsc Exp $ */

// Here are definitions for imatrix x cmatrix-Functions
#ifndef _CXSC_LRMATIMAT_HPP_INCLUDED
#define _CXSC_LRMATIMAT_HPP_INCLUDED

namespace cxsc {

	//! The accurate scalar product of the last two arguments added to the value of the first argument
	INLINE void accumulate(idotprecision &dp, const l_rmatrix_subv & rv1, const imatrix_subv &rv2)
#if(IndCheck)
	throw(OP_WITH_WRONG_DIM);
#else
	throw();
#endif
	//! The accurate scalar product of the last two arguments added to the value of the first argument
	INLINE void accumulate(idotprecision &dp, const imatrix_subv & rv1, const l_rmatrix_subv &rv2)
#if(IndCheck)
	throw(OP_WITH_WRONG_DIM);
#else
	throw();
#endif

} // namespace cxsc 
	
#endif



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

/* CVS $Id: r_tan.c,v 1.11 2008/01/23 08:39:42 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : r_tan.c                               */
/*                                                              */
/*      Entries         : a_real r_tan(a)                       */
/*                        a_real a;                             */
/*                                                              */
/*      Arguments       : a = real argument of standard function*/
/*                                                              */
/*      Description     : Tangent function                      */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
#endif

#ifdef LINT_ARGS
local a_real r_tan(a_real a)
#else
local a_real r_tan(a)

a_real a;
#endif
        {
        a_real res;
        a_btyp rc;

        E_SPUSH("r_tan")

        if ((rc = b_inv1(Ltan,a,&res,0))!=0)
           e_trap(INV_ARG,4,E_TDBL+E_TEXT(7),&a,E_TINT+E_TEXT(16),&rc);

        E_SPOPP("r_tan")
        return(res);
        }



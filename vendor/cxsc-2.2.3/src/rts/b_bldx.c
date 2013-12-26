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

/* CVS $Id: b_bldx.c,v 1.11 2008/01/23 08:39:39 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : b_bldx.c                              */
/*                                                              */
/*      Entries         : a_btyp b_bldx(a,res)                  */
/*                        a_real a;                             */
/*                        a_real res;                           */
/*                                                              */
/*      Arguments       : a = real argument of function         */
/*                      : res = real result of function         */
/*                                                              */
/*      Description     : logarithm to base 2 (exact)           */
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
local a_btyp b_bldx(a_real a,a_real *res)
#else
local a_btyp b_bldx(a,res)
a_real a;
a_real *res;
#endif

{
        a_intg expo;
        a_bool vz;
        a_btyp mant[D_U_RATIO];

        E_TPUSH("b_bldx")

        (void)b_deko(a,&expo,mant,&vz);

        if (mant[0]==HIDDEN_BIT && mant[1]==ZERO)
           {
           R_ASSIGN(*res,r_flot(expo));
           E_TPOPP("b_bldx")
           return(1);
           }

        E_TPOPP("b_bldx")
        return(0);
        }



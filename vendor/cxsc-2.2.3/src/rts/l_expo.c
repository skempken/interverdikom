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

/* CVS $Id: l_expo.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : l_expo.c                              */
/*                                                              */
/*      Entries         : a_intg l_expo(a)                      */
/*                        multiprecision a;                     */
/*                                                              */
/*      Description     : Base 2 exponent of factor of most     */
/*                        significant bit of multiprecision     */
/*                        value immediately preceding the       */
/*                        decimal point.                        */
/*                                                              */
/*      Note            : 0 returned if argument is 0.0         */
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
local a_intg l_expo(multiprecision a)
#else
local a_intg l_expo(a)

multiprecision a;
#endif
        {
        a_intg res;
        a_btyp m;

        E_TPUSH("l_expo")

        if (a->z) res = 0;
        else
           {
           res = B_LENGTH*(a->e+1)-1;
           m = a->m[0];
           while ((m & MSB)==ZERO)
              {
              res--;
              m <<=1;
              }
           }

        if (a->f) l_free(&a);

        E_TPOPP("l_expo")
        return(res);
        }


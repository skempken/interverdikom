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

/* CVS $Id: b_bivp.c,v 1.11 2008/01/23 08:39:39 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : b_bivp.c                              */
/*                                                              */
/*      Entries         : a_btyp b_bivp(func,arg,rlb,rub)       */
/*                         int (*func)();                       */
/*                         a_real arg, *rlb, *rub;              */
/*                                                              */
/*      Arguments       : func = function to be evaluated for   */
/*                               a given real argument          */
/*                        arg = point argument of function      */
/*                        rlb = lower bound of result           */
/*                        rub = upper bound of result           */
/*                                                              */
/*      Function value  : function dependent return code.       */
/*                                                              */
/*      Description     : evaluate bounds of the function value */
/*                        for a given point argument            */
/*                                                              */
/*      Note            : Rounding is required if a_real is     */
/*                        not in a base 2 representation.       */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
extern a_btyp b_maxl;
#endif

#ifdef LINT_ARGS
local a_btyp b_bivp(int (*func)(multiprecision,multiprecision),
                      a_real arg, a_real *rlb, a_real *rub)
#else
local a_btyp b_bivp(func, arg, rlb, rub)

int (*func)();
a_real arg;
a_real *rlb;
a_real *rub;
#endif
        {
        a_intg code;               /* return code of long function */
        multiprecision l_arg, l_res;
        a_btyp rc;
        a_btyp Oldb_maxl;
        a_intg down = -1, up = 1;  /* rounding mode */

        l_init(&l_arg);
        l_init(&l_res);

        /* it is assumed that there is no conversion error      */
        /* from the current real format to multiprecision       */
        if (b_rtol(arg,&l_arg,(a_intg)0)) return(ALLOCATION);

        Oldb_maxl = b_maxl;
        b_maxl = 3;

        code = (*func)(l_arg,l_res);

        rc = b_ltor(l_res,rlb,down); /* lower bound */
        rc += b_ltor(l_res,rub,up);  /* upper bound */

        b_maxl = Oldb_maxl;

        l_free(&l_arg);
        l_free(&l_res);

        return((code)?(a_btyp)code:rc);
        }


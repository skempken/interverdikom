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

/* CVS $Id: i_exp.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : i_exp.c                               */
/*                                                              */
/*      Entries         : a_intv i_exp(a)                       */
/*                        a_intv a;                             */
/*                                                              */
/*      Arguments       : a = interval argument of function     */
/*                                                              */
/*      Description     : Interval exponential function         */
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
local a_intv i_exp( a_intv a )
#else
local a_intv i_exp( a )
a_intv a;
#endif

{
        a_btyp        rc;
        a_intv          res;
        a_real          dummy;

        E_SPUSH("i_exp")

        /* --- point argument --- */
        if (i_point(a))
            {
            /* printf("point argument!\n"); */
            rc = i_invp(Lexp,a.INF,&res.INF,&res.SUP);
        }
        /* --- interval argument --- */
        else if (i_iv(a)) {
            /* printf("interval argument!\n"); */

            rc =  i_invp(Lexp,a.INF,&res.INF,&dummy);
            rc += i_invp(Lexp,a.SUP,&dummy,&res.SUP);
        }
        /* --- invalid argument --- */
        else rc = 1;

        /* --- error --- */
        if (rc)
            e_trap(INV_ARG,4,E_TDBL+E_TEXT(5),&a.INF,
                             E_TDBL+E_TEXT(6),&a.SUP);

        E_SPOPP("i_exp")
        return(res);
}



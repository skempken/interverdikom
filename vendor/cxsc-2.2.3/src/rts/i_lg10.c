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

/* CVS $Id: i_lg10.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : i_lg10.c                              */
/*                                                              */
/*      Entries         : a_intv i_lg10(a)                      */
/*                        a_intv a;                             */
/*                                                              */
/*      Arguments       : a = interval argument of function     */
/*                                                              */
/*      Description     : Interval logarithm to base 10         */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
extern a_real *r_ten_;
#endif

#ifdef LINT_ARGS
local a_intv i_lg10( a_intv a )
#else
local a_intv i_lg10( a )
a_intv a;
#endif

{
        a_btyp        rc;
        a_intv          res;
        a_real            dummy;

        E_SPUSH("i_lg10")

        /* --- invalid argument --- */
        if (r_sign(a.INF)<=0) rc = 1;

        /* --- point argument --- */
        else if ( i_point(a) ) {
            /* printf("point argument!\n"); */
            if ( i_lgex(a.INF, &dummy) ) {
                R_ASSIGN(res.INF,dummy);
                R_ASSIGN(res.SUP,dummy);
                rc = 0;
            }
            else {
              rc =  i_inv2(Lloga,a.INF,*r_ten_,&res.INF,&res.SUP);
            }
        }

        /* --- interval argument --- */
        else if ((rc = i_iv(a))!=0) {
            /* printf("interval argument!\n"); */
            if ( i_lgex(a.INF, &dummy) ) {
                rc= 0;
                R_ASSIGN(res.INF,dummy);
            }
            else {
              rc =  i_inv2(Lloga,a.INF,*r_ten_,&res.INF,&dummy);
            }

            if ( i_lgex(a.SUP, &dummy) ) {
                R_ASSIGN(res.SUP,dummy);
            }
            else {
              rc += i_inv2(Lloga,a.SUP,*r_ten_,&dummy,&res.SUP);
            }
        }
        /* --- invalid argument --- */
        else rc = 1;

        /* --- error --- */
        if (rc)
            e_trap(INV_ARG,4,E_TDBL+E_TEXT(5),&a.INF,
                             E_TDBL+E_TEXT(6),&a.SUP);

        /* --- exit --- */
        E_SPOPP("i_lg10")
        return(res);
        }



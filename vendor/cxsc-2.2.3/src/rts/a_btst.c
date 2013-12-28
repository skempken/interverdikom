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

/* CVS $Id: a_btst.c,v 1.11 2008/01/23 08:39:39 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : a_btst.c                              */
/*                                                              */
/*      Entries         : a_bool a_btst(a,m)                    */
/*                        a_intg a;                             */
/*                        a_intg m;                             */
/*                                                              */
/*      Arguments       : a = integer bit operand               */
/*                        m = bit number                        */
/*                                                              */
/*      Description     : TEST bit  of an integer a             */
/*                        m position of bit with m=0 is         */
/*                        right-most bit in integer.            */
/*                        0<=m<=31.                             */
/*                                                              */
/*      Function value  : TRUE if bit is set.                   */
/*                        FALSE if bit is not set.              */
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
local a_bool a_btst(a_intg a,a_intg m)
#else
local a_bool a_btst(a,m)

a_intg a;
a_intg m;
#endif
        {
        a_bool res;

        E_TPUSH("a_btst")

        if (m<0 || m>B_LENGTH-1)
           {
           e_trap(INDEX_RANGE,2,E_TINT+E_TEXT(13),&m);
           res = FALSE;
           }
        else if (m==B_LENGTH-1)
           res = (a<0) ? TRUE : FALSE;
        else
           res = (a & (((a_btyp)1)<<m)) ? TRUE : FALSE;

        E_TPOPP("a_btst")
        return(res);
        }



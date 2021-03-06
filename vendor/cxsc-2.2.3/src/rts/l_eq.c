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

/* CVS $Id: l_eq.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : l_eq.c                                */
/*                                                              */
/*      Entries         : a_bool l_eq(a,b)                      */
/*                        multiprecision a,b;                   */
/*                                                              */
/*      Arguments       : a = first operand                     */
/*                        b = second operand                    */
/*                                                              */
/*      Function value  : TRUE if values are equal              */
/*                        FALSE if values are not equal         */
/*                                                              */
/*      Description     : compare multiprecision values         */
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
local a_bool l_eq(multiprecision a,multiprecision b)
#else
local a_bool l_eq(a,b)

multiprecision a;
multiprecision b;
#endif
        {
        int res; /* !!! must be int !!! */

        E_TPUSH("l_eq")

        res = b_bcmp(a,b);

        if (a->f) l_free(&a);
        if (b->f) l_free(&b);

        E_TPOPP("l_eq")
        return((res==0) ? TRUE : FALSE);
        }



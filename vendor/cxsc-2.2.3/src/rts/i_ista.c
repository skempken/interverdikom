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

/* CVS $Id: i_ista.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : i_ista.c                              */
/*                                                              */
/*      Entries         : a_intv i_ista(cl,cu)                  */
/*                        dotprecision cl,cu;                   */
/*                                                              */
/*      Arguments       : cl= dotprecision value(lower bound)   */
/*                        cu= dotprecision value(upper bound)   */
/*                                                              */
/*      Description     : Round to interval                     */
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
local a_intv i_ista(dotprecision cl,dotprecision cu)
#else
local a_intv i_ista(cl,cu)

dotprecision cl;
dotprecision cu;
#endif
        {
        a_intv res;

        E_TPUSH("i_ista")

        res.INF = d_stad(cl);
        res.SUP = d_stau(cu);

        E_TPOPP("i_ista")
        return(res);
        }



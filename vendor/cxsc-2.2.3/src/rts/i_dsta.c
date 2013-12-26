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

/* CVS $Id: i_dsta.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : i_dsta.c                              */
/*                                                              */
/*      Entries         : d_otpi i_dsta(cl,cu)                  */
/*                        dotprecision cl,cu;                   */
/*                                                              */
/*      Arguments       : cl= dotprecision value(lower bound)   */
/*                        cu= dotprecision value(upper bound)   */
/*                                                              */
/*      Description     : Round to dotprecision interval        */
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
local d_otpi i_dsta(dotprecision cl,dotprecision cu)
#else
local d_otpi i_dsta(cl,cu)

dotprecision cl;
dotprecision cu;
#endif
{
        d_otpi  res;
        d_otpi  *ptemp= &res;

        E_TPUSH("i_dsta")

        d_vlcp((dotprecision*) &cl);
        d_vlcp((dotprecision*) &cu);

        d_init((dotprecision*) &(ptemp)->INF);
        d_init((dotprecision*) &(ptemp)->SUP);
  
        d_ass(&res.INF,cl);
        d_ass(&res.SUP,cu);

        d_free((dotprecision*) &cl);
        d_free((dotprecision*) &cu);

        ptemp= &res;
        d_temp((dotprecision*) &(ptemp)->INF);
        d_temp((dotprecision*) &(ptemp)->SUP);

        E_TPOPP("i_dsta")
        return res;
}


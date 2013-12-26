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

/* CVS $Id: c_psub.c,v 1.11 2008/01/23 08:39:40 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : c_psub.c                              */
/*                                                              */
/*      Entries         : void c_psub(cr,ci,a,b)                */
/*                        dotprecision *cr,*ci;                 */
/*                        a_cmpx a,b;                           */
/*                                                              */
/*      Arguments       : cr= dotprecision variable(real)       */
/*                        ci= dotprecision variable(imaginary)  */
/*                        a = complex value                     */
/*                        b = complex value                     */
/*                                                              */
/*      Description     : Subtract complex product from         */
/*                        dotprecision variable                 */
/*                        c = c-a*b                             */
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
local void c_psub(dotprecision *cr,dotprecision *ci,a_cmpx a,a_cmpx b)
#else
local void c_psub(cr,ci,a,b)

dotprecision *cr;
dotprecision *ci;
a_cmpx a;
a_cmpx b;
#endif
        {
        E_TPUSH("c_psub")

        d_psub(cr,a.RE,b.RE);
        d_padd(cr,a.IM,b.IM);
        d_psub(ci,a.IM,b.RE);
        d_psub(ci,a.RE,b.IM);

        E_TPOPP("c_psub")
        return;
        }



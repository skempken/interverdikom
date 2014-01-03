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

/* CVS $Id: a_bshf.c,v 1.11 2008/01/23 08:39:39 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : a_bshf.c                              */
/*                                                              */
/*      Entries         : a_intg a_bshf(a,m)                    */
/*                        a_intg a;                             */
/*                        a_intg m;                             */
/*                                                              */
/*      Arguments       : a = integer bit operand               */
/*                        m = shift value                       */
/*                                                              */
/*      Description     : Bit SHIFT of an integer a             */
/*                        m positions to the left if m>0, or    */
/*                        m positions to the right if m<0       */
/*                                                              */
/*      Function value  : logically SHIFTed integer a           */
/*                        represented as integer                */
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
local a_intg a_bshf(a_intg a,a_intg m)
#else
local a_intg a_bshf(a,m)

a_intg a;
a_intg m;
#endif
        {

        E_TPUSH("a_bshf")

        if (m<-B_LENGTH+1 || m>B_LENGTH-1) a = 0;
        else if (m<0) a = ((a_btyp)a)>>-m;
        else if (m>0) a <<= m;

        E_TPOPP("a_bshf")
        return(a);
        }


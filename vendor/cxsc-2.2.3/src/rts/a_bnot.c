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

/* CVS $Id: a_bnot.c,v 1.11 2008/01/23 08:39:39 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : a_bnot.c                              */
/*                                                              */
/*      Entries         : a_intg a_bnot(a)                      */
/*                        a_intg a;                             */
/*                                                              */
/*      Arguments       : a = integer bit operand               */
/*                                                              */
/*      Description     : Bit NOT operation of an integer       */
/*                                                              */
/*      Function value  : logically negated bits of             */
/*                        integers a represented as integer     */
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
local a_intg a_bnot(a_intg a)
#else
local a_intg a_bnot(a)

a_intg a;
#endif
        {

        E_TPUSH("a_bnot")

        a = ~a;

        E_TPOPP("a_bnot")
        return(a);
        }



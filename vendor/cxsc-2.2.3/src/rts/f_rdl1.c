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

/* CVS $Id: f_rdl1.c,v 1.11 2008/01/23 08:39:41 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : f_rdl1.c                              */
/*                                                              */
/*      Entry           : void f_rdl1(desc,r)                   */
/*                        f_text *desc;                         */
/*                        multiprecision *r;                    */
/*                                                              */
/*      Arguments       : desc   - device descriptor            */
/*                        r      - multiprecision variable      */
/*                                                              */
/*      Description     : perform PASCAL read(multiprecision).  */
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
local void f_rdl1(f_text *desc,multiprecision *r)
#else
local void f_rdl1(desc,r)

f_text *desc;
multiprecision *r;
#endif
        {
        E_TPUSH("f_rdl1")

        if (b_text(desc,TRUE))
           {
           l_read(desc->fp,r,(a_intg)0,(a_intg)desc->win.ch[0]);
           f_getc(desc);
           }

        E_TPOPP("f_rdl1")
        }



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

/* CVS $Id: s_subs.c,v 1.11 2008/01/23 08:39:42 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : s_subs.c                              */
/*                                                              */
/*      Entries         : s_trng s_subs(s,pos,len)              */
/*                        s_trng s;                             */
/*                        a_intg pos,len;                       */
/*                                                              */
/*      Arguments       : s = string                            */
/*                        pos = position                        */
/*                        len = length                          */
/*                                                              */
/*      Return value    : substring                             */
/*                                                              */
/*      Description     : Substring of string beginning at      */
/*                        position pos with length len.         */
/*                                                              */
/*                   void* cast in memcpy                       */
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
local s_trng s_subs(s_trng s,a_intg pos,a_intg len)
#else
local s_trng s_subs(s,pos,len)

s_trng s;
a_intg pos;
a_intg len;
#endif
        {
        s_trng res;
        size_t n;

        if (pos<=s.clen && len>0)
           {
           if (pos<1) pos = 1;
           if (len<=(n = s.clen-(size_t)pos+1)) n = (size_t) len ;
           s_init(&res,n);
           if (res.ptr!=NULL) memcpy((void*) res.ptr,(void*)(s.ptr+(pos-1)),n);
           res.clen = n;
           }
        else
           s_init(&res,(size_t)0);

        res.tmp = TRUE;

        if (s.tmp) s_free(&s);

        return(res);
        }



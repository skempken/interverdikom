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

/* CVS $Id: s_aimg.c,v 1.11 2008/01/23 08:39:42 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : s_aimg.c                              */
/*                                                              */
/*      Entries         : a_char *s_aimg(str,n,s,Totalwidth,    */
/*                                    FracDigits,rnd)           */
/*                        a_char str[];                         */
/*                        a_intg n;                             */
/*                        a_real s;                             */
/*                        a_intg rnd,Totalwidth,FracDigits;     */
/*                                                              */
/*      Arguments       : str - output string                   */
/*                        n - length of output string           */
/*                        s - IEEE value                        */
/*                        Totalwidth - total length of string   */
/*                        FracDigits - number of fraction digits*/
/*                        rnd - rounding mode                   */
/*                              -1 = round downwards            */
/*                               0 = round to nearest           */
/*                               1 = round upwards              */
/*                                                              */
/*      Description     : Convert an IEEE double format number  */
/*                        to a character string.                */
/*                                                              */
/****************************************************************/

#ifndef ALL_IN_ONE
#ifdef AIX
#include "/u/p88c/runtime/o_defs.h"
#else
#include "o_defs.h"
#endif
#define local
extern dotprecision b_cp__;
#endif

#ifdef LINT_ARGS
local a_char *s_aimg(a_char str[],a_intg n,a_real s,a_intg TotalWidth,
                     a_intg FracDigits,a_intg rnd)
#else
local a_char *s_aimg(str,n,s,TotalWidth,FracDigits,rnd)

a_char str[];
a_intg n;
a_real s;
a_intg TotalWidth;
a_intg FracDigits;
a_intg rnd;
#endif
        {
        a_intg length;
        char *buffer;
        a_intg i;

        E_TPUSH("s_aimg")

        if (TotalWidth<=0)
           {
           TotalWidth = ExpDigits+4+3*MANTL/10;
           if (TotalWidth<n && n>0) TotalWidth = n;
           }

        if (n<TotalWidth)
           {
           i = 0;
           e_trap(I_O_BUFFER,2,E_TMSG,57);
           }
        else
           {
           buffer = (char *)&b_cp__[0];

           r_outp(buffer,s,TotalWidth,FracDigits,rnd,&length);

           for (i=0;i<length;i++) str[i] = *buffer++;
           }

        while (i<n) str[i] = ' ';

        E_TPOPP("s_aimg")
        return(&str[0]);
        }



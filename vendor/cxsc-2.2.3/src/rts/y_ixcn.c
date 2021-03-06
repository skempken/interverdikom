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

/* CVS $Id: y_ixcn.c,v 1.11 2008/01/23 08:39:43 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : y_ixcn.c                              */
/*                                                              */
/*      Entry           : a_VOID y_ixcn(d,e_args)               */
/*                        y_dscp d;                             */
/*                        e_list                                */
/*                                                              */
/*      Arguments       : d - descriptor of dynamic array       */
/*                        e_args - variable argument list       */
/*                                                              */
/*      Return value    : char pointer to indexed element       */
/*                                                              */
/*      Description     : determine pointer to indexed element  */
/*                        with index checking.                  */
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
#if C_P_7
local a_VOID y_ixcn(y_dscp d,...)
#else
local a_VOID y_ixcn(d,e_args)

y_dscp d;
e_list
#endif
#else
local a_VOID y_ixcn(d,e_args)

y_dscp d;
e_list
#endif

        {
        a_btyp v = 0;
        a_intg i;
        a_intg k;
        va_list e_argv;

        E_TPUSH("y_ixcn")

        d = y_alck(d);

        e_open(d);

        for (i=0;i<((y_dscp)d)->numdim;i++)
           {
           /* possible pointer allignment problems              */
           k = e_ref(a_intg);
           if (k<((y_dscp)d)->fd[i].lbound ||
               k>((y_dscp)d)->fd[i].ubound)
              {
              e_trap(INDEX_RANGE,8,
                     E_TINT+E_TEXT(11),&i,
                     E_TINT+E_TEXT(4),&k,
                     E_TINT+E_TEXT(5),&((y_dscp)d)->fd[i].lbound,
                     E_TINT+E_TEXT(6),&((y_dscp)d)->fd[i].ubound);
              }
           v += (k-((y_dscp)d)->fd[i].lbound)* ((y_dscp)d)->fd[i].stride;
           }

        e_shut;

        E_TPOPP("y_ixcn")
        return((char *)(((y_dscp)d)->array)+v*((y_dscp)d)->elsize);
        }



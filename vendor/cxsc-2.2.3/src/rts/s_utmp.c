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

/* CVS $Id: s_utmp.c,v 1.11 2008/01/23 08:39:42 cxsc Exp $ */

/****************************************************************/
/*                                                              */
/*      Filename        : s_utmp.c                              */
/*                                                              */
/*      Entry           : void s_utmp(d)                        */
/*                        s_trng *d;                            */
/*                                                              */
/*      Arguments       : d - descriptor of dynamic string      */
/*                                                              */
/*      Description     : reset temporary flag                  */
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
local void s_utmp(s_trng *d)
#else
local void s_utmp(d)

s_trng *d;
#endif
        {
        d->tmp = FALSE;
        return;
        }



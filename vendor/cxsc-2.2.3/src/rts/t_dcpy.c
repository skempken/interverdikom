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

/* CVS $Id: t_dcpy.c,v 1.11 2008/01/23 08:39:43 cxsc Exp $ */

#ifdef AIX
#include "/u/p88c/runtime/tbyte/t_ddev.h"
#else
#include "t_ddev.h"
#endif

/*--------------------------------------------------------------*/
/* copydd                                                       */
/*--------------------------------------------------------------*/
#ifdef ANSI_C
#ifdef LINT_ARGS
int copydd(const DReal *arg, DReal *res)
#else
int copydd(arg, res)
const DReal   *arg;
      DReal   *res;
#endif /* LINT_ARGS */
#else  /* NOT ANSI_C */
#ifdef LINT_ARGS
int copydd(DReal *arg, DReal *res)
#else
int copydd(arg, res)
DReal   *arg;
DReal   *res;
#endif /* LINT_ARGS */
#endif /* ANSI_C */
{
   memcpy(res, arg, sizeof(DReal));
   return 0;

} /* copydd() */



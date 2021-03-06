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

/* CVS $Id: t_ctoe.c,v 1.11 2008/01/23 08:39:43 cxsc Exp $ */


#ifdef AIX
#include "/u/p88c/runtime/tbyte/t_defs.h"
#else
#include "t_defs.h"
#endif

/*--------------------------------------------------------------*
 | condition-code ==> exception-code                            |
 *--------------------------------------------------------------*/
#ifdef LINT_ARGS
int cond_to_exc(int condition)
#else
int cond_to_exc(condition)
int condition;
#endif /* LINT_ARGS */
{
   switch(condition) {
   case PUnorm:  return ExcPUnorm;
   case PNAN:    return ExcPNAN;
   case MUnorm:  return ExcMUnorm;
   case MNAN:    return ExcMNAN;
   case PNorm:   return ExcPNorm;
   case PInf:    return ExcPInf;
   case MNorm:   return ExcMNorm;
   case MInf:    return ExcMInf;
   case PZero:   return ExcPZero;
   case Empty1:  return ExcEmpty;
   case MZero:   return ExcMZero;
   case Empty2:  return ExcEmpty;
   case PDenorm: return ExcPDenorm;
   case MDenorm: return ExcMDenorm;
   default:      return ExcUnknown;
   }
} /* cond_to_exc() */



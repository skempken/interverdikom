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

/* CVS $Id: t_cher.c,v 1.11 2008/01/23 08:39:43 cxsc Exp $ */


#ifdef AIX
#include "/u/p88c/runtime/tbyte/t_defs.h"
#else
#include "t_defs.h"
#endif

/*--------------------------------------------------------------*
 | check ExtReal Argument                                       |
 *--------------------------------------------------------------*/
#ifdef ANSI_C
#ifdef LINT_ARGS
int chk_extreal(const ExtReal *arg, const int code)
#else
int chk_extreal(arg, code)
const ExtReal *arg; /* zu ueberpruefendes Argument                    */
const int code;     /* condition codes, auf die geprueft werden soll  */
#endif /* LINT_ARGS */
#else  /* NOT ANSI_C */
#ifdef LINT_ARGS
int chk_extreal(ExtReal *arg, int code)
#else
int chk_extreal(arg, code)
ExtReal  *arg;       /* zu ueberpruefendes Argument                    */
int code;            /* condition codes, auf die geprueft werden soll  */
#endif /* LINT_ARGS */
#endif /* ANSI_C */
{
   int condition_code;
   int err_typ = 0;

   if(0==(code & (condition_code = _s_xam(arg))))
        err_typ=cond_to_exc(condition_code);
   else
      /* --- pruefe auf unsupported 8087 Unnormals --- */
      if(-1==cmpabsee(arg, &MinNormExtReal))
         /* Unormals sind < Denormals */
      if(_s_chk_invalid(arg)) err_typ = ExcInvalid;

   return err_typ;
} /* chk_extreal() */



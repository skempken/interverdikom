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

/* CVS $Id: b_cos_.c,v 1.12 2008/01/23 08:39:39 cxsc Exp $ */

/*************************************************************************
 *                                                                       *
 * Descriptive Name : Lcos               Processor : C                   *
 *                                                                       *
 * Cosine Function for Multiple Precision Arithmetic                     *
 * =================================================                     *
 *                                                                       *
 * Include files :  b_lari.h  - definitions for INTERN standard functions*
 *                                                                       *
 * Function value : int       - 0                                        *
 *                                                                       *
 * Argument Range :    All nonnegative numbers                           *
 * Result Range :      Nonnegative numbers                               *
 *                                                                       *
 * Used Functions :                                                      *
 *    sicovea         Computation of function value and error bound      *
 *    Lassign         Assignment of function value and number of ulp's   *
 *                                                                       *
 * Used Global INTERN Variables and Constants :                          *
 *    LhF, LhD        Sine and cosine, resp., of argument                *
 *    LhE             Used for debugging only                            *
 *                                                                       *
 * Used UNSIGNED Global Variables :                                      *
 *    Maxl            Length of INTERN Variables                         *
 *    Lcurrprec       Initial Length of INTERN Variables                 *
 *    Ldebug          Flag for printing additional information           *
 *    Lversion        Flag for printing additional information           *
 *                                                                       *
 *************************************************************************/

#define  Name        "Lcos"
#define  Main

#ifdef AIX
#include "/u/p88c/runtime/base/b_lari.h"
#else
#include "b_lari.h"
#endif

static char  *function = Name;

/************************************************************************
 * Algorithm                                                            *
 ************************************************************************/

#ifdef LINT_ARGS
int b_cos_(dynamic *xi,dynamic *ri)
#else
int b_cos_(xi,ri)

dynamic *xi;
dynamic *ri;
#endif
#define  LRoutine    "Lcos"
{
   extern dynamic   LhF, LhD, Lone;
   extern a_btyp  Maxl;
   extern a_btyp  Lcurrprec;
   extern char      *Lroutine;
   extern a_btyp LhI;  /* entier(x/(pi/4)) mod 16 when calling sin(x) */

   int    rc;
#define poolvars  0

#ifdef Debug
   extern int       Ldebug;
   extern dynamic   LhE;
#endif

#ifdef Debug
   Ldebug -= 1;                            /* Diminish Debug Level      */
   if (Ldebug >= 0) printf("\n Entering Routine %s",LRoutine);
#endif

  /*----------------*
   | Initialization |
   *----------------*/

   Lroutine = function;
   Lcurrprec = Maxl;            /* Save precision setting       */
   rc = 0;
   LhI = 0;

  /*----------------------------*
   | Check and Handle Case xi=0 |
   *----------------------------*/

   if (xi->z == 1) {
      COPY_(&Lone,ri);          /* ri = cos(0) = 1              */
      if (rc != 0) {
         ERREXIT(rc,115,0);     /* Error message and handling   */
         }
      ri->r = 0;
      EXIT(0);
      }


  /*-------------------------------------*
   | Check and Handle Undefined Mantissa |
   *-------------------------------------*/

   if (xi->m[0] == 0) {
      ERREXIT(NANDE,NANDE,0);   /* Error message and handling   */
      }

   SICO_(xi);           /* Compute function value and error bound */

#ifdef Debug
   if (Ldebug >= 0) {
      printf("\n  (Lcos 134) LhD = ");  Lprinti(&LhD);
      printf("\n  (Lcos 135) LhE = ");  Lprinti(&LhE);
      }
#endif

   Maxl = LhD.l;
   COPY_(&LhD,&LhF);

#if INT_HPREC
   b_case = LESS_ABS_ONE;
#endif

   ASSIGN_(ri);         /* Assign cosine and set number of ulp's */

#ifdef Debug
   if (Ldebug >= 0) {
      printf("\n  (Lcos 145) cos = ");  Lprinti(ri);
      printf("   (+ %d ulp)",ri->r);
      }
#endif

   RETURN(0);
}



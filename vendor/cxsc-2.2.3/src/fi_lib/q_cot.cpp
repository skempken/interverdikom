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

/* CVS $Id: q_cot.cpp,v 1.5 2008/01/23 08:39:36 cxsc Exp $ */

#ifndef Q_COT_CPP
#define Q_COT_CPP

#include "fi_lib.hpp" 

namespace fi_lib {

 using cxsc::real;
 
 real q_cot(real x){
  real res;
  long int m,n,k;
  real ysq,y,q,s,c;


  /* Special cases  */
  if(NANTEST(x))                                 /* Test: x=NaN */
      res=q_abortnan(INV_ARG,&x,13);
  else {
  if ((x<-q_sint[2])||(x>q_sint[2]))
      res=q_abortr1(INV_ARG,&x,13);             /* abs. argument too big */

  /* Argument reduction */
  if ((x>-q_minr)&&(x<q_minr))
     res=q_abortr1(INV_ARG,&x,13);
  else {
     y=x*q_pi2i; 
     if (y>0) k=CUTINT(y+0.5); else k=CUTINT(y-0.5);
     y=q_rtrg(x,k); 
     n=k%4; if (n<0) n+=4; m=n%2; 

     /* Approximation */
     ysq=y*y;

     /* Computation sine */
     if ((-q_sint[3]<y)&&(y<q_sint[3]))
      {
        if (n==0) s=y; 
        else s=-y;
      }
     else
     {
       q=ysq*(((((((q_sins[5]*ysq)+q_sins[4])
         *ysq+q_sins[3])*ysq+q_sins[2])*ysq+q_sins[1])*ysq)+q_sins[0]);
       if (n==0)
         s=y+y*q;
       else
         s=-(y+y*q);
     }  
 
     /* Computation cosine */
     q=ysq*ysq*(((((((q_sinc[5]*ysq)+q_sinc[4])
         *ysq+q_sinc[3])*ysq+q_sinc[2])*ysq+q_sinc[1])*ysq)+q_sinc[0]);

     if (ysq >= q_sint[0])
       c=0.625+(0.375-(0.5*ysq)+q);
     else if (ysq >= q_sint[1])
       c=0.8125+((0.1875-(0.5*ysq))+q);
     else
       c=1.0-(0.5*ysq - q);
     if (n==2) c=-c; 
 
 
     /* Computation cotangens */
     if (m==0) res=c/s;
     else      res=s/c;
   }
  }

  return(res);
 } 

} // Namepace 

#endif



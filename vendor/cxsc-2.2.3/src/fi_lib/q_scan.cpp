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

/* CVS $Id: q_scan.cpp,v 1.5 2008/01/23 08:39:36 cxsc Exp $ */

#ifndef Q_SCAN_CPP
#define Q_SCAN_CPP

#include <cmath>
#include "fi_lib.hpp" 

namespace fi_lib{

 using cxsc::real;

 real scandown()
 {
  real x;
  std::cin >> x;
  if (fabs(_double(x))>(1e17-1)*1e27) 
    return q_pred(q_pred(x));
  else return q_pred(x);
 }

 real scanup()
 {
  real x;
  std::cin >> x;
  if (fabs(_double(x))>(1e17-1)*1e27) 
    return q_succ(q_succ(x));
  else return q_succ(x);
 }

 interval scanInterval()
 { 
  interval dummy;
  Inf(dummy) = scandown();
  Sup(dummy) = scanup();
  return dummy;
 }

} // Namespace

#endif



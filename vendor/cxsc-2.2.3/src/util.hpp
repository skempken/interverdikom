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

/* CVS $Id: util.hpp,v 1.4 2008/01/23 08:39:32 cxsc Exp $ */

#ifndef util_hpp_included
#define util_hpp_included

#include <iostream>

namespace cxsc {
inline int add_int(int a,int b)
// Calculating a+b; abortion by int overflow.
{
   int res(a+b);
   bool bl1(a>0 && b>0 && res<a),
        bl2(a<0 && b<0 && res>a);
   if (bl1||bl2)
   {
       std::cerr << "ERROR in int add_int(int,int): Overflow!" << std::endl;
       exit(1);	 
   }
   return res;
}

inline int sub_int(int a,int b)
// Calculating a-b; abortion by int overflow.
{
   if (b<0 && -b<0)
   { 
       std::cerr << "ERROR in int sub_int(int,int): Overflow!" << std::endl;
       exit(1);
   }
   return add_int(a,-b);
}

} // namespace cxsc 

#endif


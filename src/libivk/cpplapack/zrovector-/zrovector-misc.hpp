//=============================================================================
/*! clear vector */
inline void zrovector::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG

  L =0;
  delete [] Array;
  Array =NULL;
}

//=============================================================================
/*! make vector into zero vector */
inline void zrovector::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =std::complex<double>(0.0,0.0); }
}

//=============================================================================
/*! change sign(+/-) of the vector */
inline void zrovector::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the zrovector */
inline void zrovector::copy(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::copy(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::copy(const zrovector&) "
            << "A zrovector at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =new std::complex<double>[vec.L];
  zcopy_(vec.L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a zrovector has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the vector\n
 This function is not desinged to be used in project codes. */
inline void zrovector::shallow_copy(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::shallow_copy(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::shallow_copy(const _zrovector&) "
            << "A zrovector at " << Array << " is going to be deleted "
            << "and point at " << vec.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =vec.Array;
}

//=============================================================================
/*! resize vector */
inline void zrovector::resize(const long& _l)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] zrovector::resize(const long&)" << std::endl
              << "Vector size must be positive integers." << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  L =_l;
  delete [] Array;
  Array =new std::complex<double>[_l];
}

//=============================================================================
/*! swap two vectors */
inline void swap(zrovector& u, zrovector& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zrovector&, zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long u_L(u.L);
  std::complex<double>* u_Array(u.Array);
  u.L=v.L; u.Array=v.Array;
  v.L=u_L; v.Array=u_Array;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zrovector _(zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zrovector newvec;

  newvec.L =vec.L;
  newvec.Array =vec.Array;

  vec.L =0;
  vec.Array =NULL;

  return newvec;
}

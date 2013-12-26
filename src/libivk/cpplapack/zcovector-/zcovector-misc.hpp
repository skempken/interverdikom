//=============================================================================
/*! clear vector */
inline void zcovector::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG

  L =0;
  delete [] Array;
  Array =NULL;
}

//=============================================================================
/*! make vector into zero vector */
inline void zcovector::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =std::complex<double>(0.0,0.0); }
}

//=============================================================================
/*! change sign(+/-) of the vector */
inline void zcovector::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the zcovector */
inline void zcovector::copy(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::copy(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::copy(const zcovector&) "
            << "A zcovector at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =new std::complex<double>[vec.L];
  zcopy_(vec.L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a zcovector has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the vector\n
 This function is not desinged to be used in project codes. */
inline void zcovector::shallow_copy(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::shallow_copy(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::shallow_copy(const _zcovector&) "
            << "A zcovector at " << Array << " is going to be deleted "
            << "and point at " << vec.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =vec.Array;
}

//=============================================================================
/*! resize vector */
inline void zcovector::resize(const long& _l)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] zcovector::resize(const long&)" << std::endl
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
inline void swap(zcovector& u, zcovector& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zcovector&, zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long u_l(u.L);
  std::complex<double>* u_array(u.Array);
  u.L=v.L; u.Array=v.Array;
  v.L=u_l; v.Array=u_array;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zcovector _(zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zcovector newvec;

  newvec.L =vec.L;
  newvec.Array =vec.Array;

  vec.L =0;
  vec.Array =NULL;

  return newvec;
}

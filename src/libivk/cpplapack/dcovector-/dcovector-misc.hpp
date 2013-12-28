//=============================================================================
/*! clear vector */
inline void dcovector::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG

  L =0;
  delete [] Array;
  Array =NULL;
}

//=============================================================================
/*! make vector into zero vector */
inline void dcovector::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =0.0; }
}

//=============================================================================
/*! change sign(+/-) of the vector */
inline void dcovector::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the dcovector */
inline void dcovector::copy(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::copy(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::copy(const dcovector&) "
            << "A dcovector at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =new double[vec.L];
  dcopy_(vec.L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a dcovector has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the vector\n
 This function is not desinged to be used in project codes. */
inline void dcovector::shallow_copy(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::shallow_copy(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::shallow_copy(const _dcovector&) "
            << "A dcovector at " << Array << " is going to be deleted "
            << "and point at " << vec.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =vec.Array;
}

//=============================================================================
/*! resize vector */
inline void dcovector::resize(const long& _l)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] dcovector::resize(const long&)" << std::endl
              << "Vector size must be positive integers." << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  L =_l;
  delete [] Array;
  Array =new double[_l];
}

//=============================================================================
/*! swap two vectors */
inline void swap(dcovector& u, dcovector& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(dcovector&, dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long u_l(u.L);
  double* u_array(u.Array);
  u.L=v.L; u.Array=v.Array;
  v.L=u_l; v.Array=u_array;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _dcovector _(dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _dcovector newvec;
  
  newvec.L =vec.L;
  newvec.Array =vec.Array;

  vec.L =0;
  vec.Array =NULL;

  return newvec;
}

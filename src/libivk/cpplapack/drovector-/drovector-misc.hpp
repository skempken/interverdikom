//=============================================================================
/*! clear vector */
inline void drovector::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG

  L =0;
  delete [] Array;
  Array =NULL;
}

//=============================================================================
/*! make vector into zero vector */
inline void drovector::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =0.0; }
}

//=============================================================================
/*! change sign(+/-) of the vector */
inline void drovector::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<L; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the drovector */
inline void drovector::copy(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::copy(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::copy(const drovector&) "
            << "A drovector at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =new double[vec.L];
  dcopy_(vec.L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a drovector has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the vector\n
 This function is not desinged to be used in project codes. */
inline void drovector::shallow_copy(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::shallow_copy(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::shallow_copy(const _drovector&) "
            << "A drovector at " << Array << " is going to be deleted "
            << "and point at " << vec.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  L =vec.L;
  Array =vec.Array;
}

//=============================================================================
/*! resize vector */
inline void drovector::resize(const long& _l)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] drovector::resize(const long&)" << std::endl
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
inline void swap(drovector& u, drovector& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(drovector&, drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long u_L(u.L);
  double* u_Array(u.Array);
  u.L=v.L; u.Array=v.Array;
  v.L=u_L; v.Array=u_Array;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _drovector _(drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _drovector newvec;

  newvec.L =vec.L;
  newvec.Array =vec.Array;
  
  vec.L =0;
  vec.Array =NULL;
  
  return newvec;
}

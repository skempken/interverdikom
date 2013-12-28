//=============================================================================
/*! return a transposed column vector */
inline _dcovector t(const _drovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _dcovector covec;
  covec.L =rovec.L;
  delete [] covec.Array;
  covec.Array =rovec.Array;
  
  return covec;
}

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( dnrm2_(vec.L, vec.Array, 1) );
  vec.destroy();
  return val;
}

//=============================================================================
/*! return the index of element having the largest absolute value
  in 0-based numbering system */
inline long idamax(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long i( idamax_(vec.L, vec.Array, 1) -1 );
  vec.destroy();
  return i;
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( vec.Array[idamax_(vec.L, vec.Array, 1)-1] );
  vec.destroy();
  return val;
}

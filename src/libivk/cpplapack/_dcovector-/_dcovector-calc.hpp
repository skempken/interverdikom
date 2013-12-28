//=============================================================================
/*! return a transposed row vector */
inline drovector t(const _dcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _drovector rovec;
  rovec.L =covec.L;
  delete [] rovec.Array;
  rovec.Array =covec.Array;
  
  return rovec;
}

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( dnrm2_(vec.L, vec.Array, 1) );
  vec.destroy();
  return val;
}

//=============================================================================
/*! return the index of element having the largest absolute value
 in 0-based numbering system */
inline long idamax(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long i( idamax_(vec.L, vec.Array, 1) -1 );
  vec.destroy();
  return i;
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( vec.Array[idamax_(vec.L, vec.Array, 1)-1] );
  vec.destroy();
  return val;
}

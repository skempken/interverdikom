//=============================================================================
/*! return a transposed row vector */
inline _zrovector t(const _zcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _zrovector rovec;
  rovec.L =covec.L;
  delete [] rovec.Array;
  rovec.Array =covec.Array;
  
  return rovec;
}

//=============================================================================
/*! return its conjugated vector */
inline _zcovector conj(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec(i) =std::conj(vec(i)); }
  return vec;
}

//=============================================================================
/*! return a conjugate transposed row vector */
inline _zrovector conjt(const _zcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector rovec(covec.L);
  for(long i=0; i<covec.L; i++){ rovec(i) =std::conj(covec(i)); }
  
  covec.destroy();
  return _(rovec);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( dznrm2_(vec.L, vec.Array, 1) );
  vec.destroy();
  return val;
}

//=============================================================================
/*! return the index of element having the largest absolute value
 in 0-based numbering system */
inline long idamax(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long i( izamax_(vec.L, vec.Array, 1) -1 );
  vec.destroy();
  return i;
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> val( vec.Array[izamax_(vec.L, vec.Array, 1)-1] );
  vec.destroy();
  return val;
}

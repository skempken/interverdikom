//=============================================================================
/*! return a transposed column vector */
inline _zcovector t(const _zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _zcovector covec;
  covec.L =rovec.L;
  delete [] covec.Array;
  covec.Array =rovec.Array;
  
  return covec;
}

//=============================================================================
/*! return its conjugated vector */
inline _zrovector conj(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ vec(i) =std::conj(vec(i)); }
  return vec;
}

//=============================================================================
/*! return a conjugate transposed column vector */
inline _zcovector conjt(const _zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector covec(rovec.L);
  for(long i=0; i<rovec.L; i++){ covec(i) =std::conj(rovec(i)); }
  
  rovec.destroy();
  return _(covec);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( dznrm2_(vec.L, vec.Array, 1) );
  vec.destroy();
  return val;
}

//=============================================================================
/*! return the index of element having the largest absolute value
  in 0-based numbering system */
inline long idamax(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long i( izamax_(vec.L, vec.Array, 1) -1 );
  vec.destroy();
  return i;
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> val( vec.Array[izamax_(vec.L, vec.Array, 1)-1] );
  vec.destroy();
  return val;
}

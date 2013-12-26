//=============================================================================
/*! return a transposed row vector */
inline _zrovector t(const zcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector rovec(covec.L);
  zcopy_(covec.L, covec.Array, 1, rovec.array, 1);
  
  return _(rovec);
}
//=============================================================================
/*! return its conjugated vector */
inline _zcovector conj(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec(i) =std::conj(vec(i)); }
  
  return _(newvec);
}

//=============================================================================
/*! return a conjugate transposed row vector */
inline _zrovector conjt(const zcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector rovec(covec.L);
  for(long i=0; i<covec.L; i++){ rovec(i) =std::conj(covec(i)); }
  
  return _(rovec);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return dznrm2_(vec.L, vec.Array, 1);
}

//=============================================================================
/*! return the index of element having the largest absolute value
 in 0-based numbering system */
inline long idamax(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return izamax_(vec.L, vec.Array, 1) -1;
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec.Array[izamax_(vec.L, vec.Array, 1) -1];
}

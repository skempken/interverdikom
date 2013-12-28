//=============================================================================
/*! return a transposed column vector */
inline _zcovector t(const zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector covec(rovec.L);
  zcopy_(rovec.L, rovec.Array, 1, covec.array, 1);
  
  return _(covec);
}

//=============================================================================
/*! return its conjugated vector */
inline _zrovector conj(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conj(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec(i) =std::conj(vec(i)); }
  
  return _(newvec);
}

//=============================================================================
/*! return a conjugate transposed column vector */
inline _zcovector conjt(const zrovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] conjt(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zcovector covec(rovec.L);
  for(long i=0; i<rovec.L; i++){ covec(i) =std::conj(rovec(i)); }
  
  return _(covec);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return dznrm2_(vec.L, vec.Array, 1);
}

//=============================================================================
/*! return the index of element having the largest absolute value
  in 0-based numbering system */
inline long idamax(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return izamax_(vec.L, vec.Array, 1) -1;
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec.Array[izamax_(vec.L, vec.Array, 1) -1];
}

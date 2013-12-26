//=============================================================================
/*! return a transposed row vector */
inline _drovector t(const dcovector& covec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  drovector rovec(covec.L);
  dcopy_(covec.L, covec.Array, 1, rovec.array, 1);
  
  return _(rovec);
}

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return dnrm2_(vec.L, vec.Array, 1);
}

//=============================================================================
/*! return the index of element having the largest absolute value
 in 0-based numbering system */
inline long idamax(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return idamax_(vec.L, vec.Array, 1) -1;
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec.Array[idamax_(vec.L, vec.Array, 1) -1];
}

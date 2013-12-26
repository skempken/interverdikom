//=============================================================================
/*! return a transposed column vector */
inline _dcovector t(const drovector& rovec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dcovector covec(rovec.L);
  dcopy_(rovec.L, rovec.Array, 1, covec.array, 1);
  
  return _(covec);
}

//=============================================================================
/*! return its Euclidean norm */
inline double nrm2(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] nrm2(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return dnrm2_(vec.L, vec.Array, 1);
}

//=============================================================================
/*! return the index of element having the largest absolute value
  in 0-based numbering system */
inline long idamax(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return idamax_(vec.L, vec.Array, 1) -1;
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return vec.Array[idamax_(vec.L, vec.Array, 1) -1];
}

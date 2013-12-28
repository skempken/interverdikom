//=============================================================================
/*! +_dgematrix operator */
inline const _dgematrix& operator+(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_dgematrix operator */
inline _dgematrix operator-(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M*mat.N; i++){ mat.Array[i]=-mat.Array[i]; }
  
  return mat;
}

//=============================================================================
/*! +_zgematrix operator */
inline const _zgematrix& operator+(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_zgematrix operator */
inline _zgematrix operator-(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M*mat.N; i++){ mat.Array[i]=-mat.Array[i]; }
  return mat;
}

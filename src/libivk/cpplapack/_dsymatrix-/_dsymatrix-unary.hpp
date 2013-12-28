//=============================================================================
/*! +_dsymatrix operator */
inline const _dsymatrix& operator+(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_dsymatrix operator */
inline _dsymatrix operator-(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.N*mat.N; i++){ mat.Array[i]=-mat.Array[i]; }
  return mat;
}

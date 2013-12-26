//=============================================================================
/*! +_dgbmatrix operator */
inline const _dgbmatrix& operator+(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_dgbmatrix operator */
inline _dgbmatrix operator-(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(mat.KL+mat.KU+1)*mat.N; i++){
    mat.Array[i]=-mat.Array[i];
  }
  
  return mat;
}

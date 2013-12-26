//=============================================================================
/*! +_zgbmatrix operator */
inline const _zgbmatrix& operator+(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix& operator+(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -_zgbmatrix operator */
inline _zgbmatrix operator-(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(mat.KL+mat.KU+1)*mat.N; i++){
    mat.Array[i]=-mat.Array[i];
  }
  return mat;
}

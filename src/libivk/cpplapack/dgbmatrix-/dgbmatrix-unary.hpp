//=============================================================================
/*! +dgbmatrix operator */
inline const dgbmatrix& operator+(const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -dgbmatrix operator */
inline _dgbmatrix operator-(const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgbmatrix newmat(mat.M,mat.N,mat.KL,mat.KU);
  for(long i=0; i<(newmat.KL+newmat.KU+1)*newmat.N; i++){
    newmat.Array[i]=-mat.Array[i];
  }
  
  return _(newmat);
}

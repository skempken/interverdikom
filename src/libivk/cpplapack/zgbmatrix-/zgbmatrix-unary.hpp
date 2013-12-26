//=============================================================================
/*! +zgbmatrix operator */
inline const zgbmatrix& operator+(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator+(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat;
}

//=============================================================================
/*! -zgbmatrix operator */
inline _zgbmatrix operator-(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator-(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.M,mat.N,mat.KL,mat.KU);
  for(long i=0; i<(newmat.kl+newmat.ku+1)*newmat.n; i++){
    newmat.array[i]=-mat.Array[i];
  }
  
  return _(newmat);
}

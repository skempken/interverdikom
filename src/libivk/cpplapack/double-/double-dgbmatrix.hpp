//=============================================================================
/*! double*dgbmatrix operator */
inline _dgbmatrix operator*(const double& d, const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.kl+newmat.ku+1)*newmat.n; i++){
    newmat.Array[i] =d*mat.Array[i];
  }
  return _(newmat);
}

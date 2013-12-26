//=============================================================================
/*! std::complex<double>*zgbmatrix operator */
inline _zgbmatrix operator*(const std::complex<double>& d, const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgbmatrix newmat(mat.M, mat.N, mat.KL, mat.KU);
  for(long i=0; i<(newmat.KL+newmat.KU+1)*newmat.N; i++){
    newmat.Array[i] =d*mat.Array[i];
  }
  
  return _(newmat);
}

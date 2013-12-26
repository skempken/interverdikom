//=============================================================================
/*! std::complex<double>*zhematrix operator */
inline _zgematrix operator*(const std::complex<double>& d, const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  mat.complete();
  zgematrix newmat(mat.N, mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.array[i] =d*mat.Array[i]; }
  
  return _(newmat);
}

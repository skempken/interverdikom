//=============================================================================
/*! zhematrix*std::complex<double> operator */
inline _zgematrix operator*(const zhematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  mat.complete();
  zgematrix newmat(mat.N, mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.array[i] =mat.Array[i]*d; }
  
  return _(newmat);
}

//=============================================================================
/*! zhematrix/std::complex<double> operator */
inline _zgematrix operator/(const zhematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zhematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> inv_d(1./d);
  
  mat.complete();
  zgematrix newmat(mat.N, mat.N);
  for(long i=0; i<mat.N*mat.N; i++){ newmat.array[i] =mat.Array[i]*inv_d; }
  
  return _(newmat);
}

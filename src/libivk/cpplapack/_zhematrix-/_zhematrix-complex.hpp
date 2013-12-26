//=============================================================================
/*! _zhematrix*std::complex<double> operator */
inline _zgematrix operator*(const _zhematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zhematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat);
  zscal_(mat.N*mat.N, d, newmat.array, 1);
  
  return _(newmat);
}

//=============================================================================
/*! zhematrix/std::complex<double> operator */
inline _zgematrix operator/(const _zhematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zhematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zgematrix newmat(mat);
  zscal_(mat.N*mat.N, 1./d, newmat.array, 1);
  
  return _(newmat);
}

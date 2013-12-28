//=============================================================================
/*! _zgematrix*std::complex<double> operator */
inline _zgematrix operator*(const _zgematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.M*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgematrix/std::complex<double> operator */
inline _zgematrix operator/(const _zgematrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zgematrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(mat.M*mat.N, 1./d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgbmatrix*std::complex<double> operator */
inline _zgbmatrix operator*(const _zgbmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgbmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgbmatrix/std::complex<double> operator */
inline _zgbmatrix operator/(const _zgbmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zgbmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_((mat.KL+mat.KU+1)*mat.N, 1./d, mat.Array, 1);
  return mat;
}

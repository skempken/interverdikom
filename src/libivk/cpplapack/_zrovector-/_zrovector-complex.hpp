//=============================================================================
/*! _zrovector*std::complex<double> operator */
inline _zrovector operator*(const _zrovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zrovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, d, vec.Array, 1);  
  return vec;
}

//=============================================================================
/*! _zrovector/std::complex<double> operator */
inline _zrovector operator/(const _zrovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zrovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

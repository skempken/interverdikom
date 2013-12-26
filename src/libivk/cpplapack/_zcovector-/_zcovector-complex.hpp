//=============================================================================
/*! _zcovector*std::complex<double> operator */
inline _zcovector operator*(const _zcovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zcovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _zcovector/std::complex<double> operator */
inline _zcovector operator/(const _zcovector& vec, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zcovector&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

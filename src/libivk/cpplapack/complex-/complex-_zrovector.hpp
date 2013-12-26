//=============================================================================
/*! std::complex<double>*_zrovector operator */
inline _zrovector operator*(const std::complex<double>& d, const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, d, vec.Array, 1);  
  return vec;
}

//=============================================================================
/*! std::complex<double>*_zcovector operator */
inline _zcovector operator*(const std::complex<double>& d, const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const std::complex<double>&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(vec.L, d, vec.Array, 1);  
  return vec;
}

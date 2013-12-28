//=============================================================================
/*! double*_zrovector operator */
inline _zrovector operator*(const double& d, const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, d, vec.Array, 1);
  return vec;
}

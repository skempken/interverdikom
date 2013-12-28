//=============================================================================
/*! double*_dcovector operator */
inline _dcovector operator*(const double& d, const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, d, vec.Array, 1);
  return vec;
}

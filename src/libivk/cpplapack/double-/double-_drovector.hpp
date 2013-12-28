//=============================================================================
/*! double*_drovector operator */
inline _drovector operator*(const double& d, const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, d, vec.Array, 1);  
  return vec;
}

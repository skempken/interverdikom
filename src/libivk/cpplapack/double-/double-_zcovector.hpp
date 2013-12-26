//=============================================================================
/*! double*_zcovector operator */
inline _zcovector operator*(const double& d, const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, d, vec.Array, 1);
  return vec;
}

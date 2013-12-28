//=============================================================================
/*! _zcovector*double operator */
inline _zcovector operator*(const _zcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _zcovector/double operator */
inline _zcovector operator/(const _zcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

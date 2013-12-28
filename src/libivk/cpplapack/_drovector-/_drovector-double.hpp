//=============================================================================
/*! _drovector*double operator */
inline _drovector operator*(const _drovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _drovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _drovector/double operator */
inline _drovector operator/(const _drovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _drovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

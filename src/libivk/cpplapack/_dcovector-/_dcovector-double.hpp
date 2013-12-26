//=============================================================================
/*! _dcovector*double operator */
inline _dcovector operator*(const _dcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _dcovector/double operator */
inline _dcovector operator/(const _dcovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _dcovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _zrovector*double operator */
inline _zrovector operator*(const _zrovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zrovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, d, vec.Array, 1);
  return vec;
}

//=============================================================================
/*! _zrovector/double operator */
inline _zrovector operator/(const _zrovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zrovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(vec.L, 1./d, vec.Array, 1);
  return vec;
}

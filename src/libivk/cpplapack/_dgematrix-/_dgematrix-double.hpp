//=============================================================================
/*! _dgematrix*double operator */
inline _dgematrix operator*(const _dgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.M*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _dgematrix/double operator */
inline _dgematrix operator/(const _dgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _dgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.M*mat.N, 1./d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgematrix*double operator */
inline _zgematrix operator*(const _zgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.M*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zgematrix/double operator */
inline _zgematrix operator/(const _zgematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zgematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.M*mat.N, 1./d, mat.Array, 1);
  return mat;
}

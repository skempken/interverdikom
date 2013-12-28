//=============================================================================
/*! _zhematrix*double operator */
inline _zhematrix operator*(const _zhematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zhematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.N*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! _zhematrix/double operator */
inline _zhematrix operator/(const _zhematrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _zhematrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.N*mat.N, 1./d, mat.Array, 1);
  return mat;
}

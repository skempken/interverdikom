//=============================================================================
/*! _dsymatrix*double operator */
inline _dsymatrix operator*(const _dsymatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dsymatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.N*mat.N, d, mat.Array, 1);
  return mat;
}

//=============================================================================
/*! dsymatrix/double operator */
inline _dsymatrix operator/(const _dsymatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const _dsymatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.N*mat.N, 1./d, mat.Array, 1);
  return mat;
}

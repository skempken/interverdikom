//=============================================================================
/*! double*_dsymatrix operator */
inline _dsymatrix operator*(const double& d, const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.N*mat.N, d, mat.Array, 1);
  return mat;
}

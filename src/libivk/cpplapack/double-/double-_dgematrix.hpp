//=============================================================================
/*! double*_dgematrix operator */
inline _dgematrix operator*(const double& d, const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(mat.M*mat.N, d, mat.Array, 1);
  return mat;
}

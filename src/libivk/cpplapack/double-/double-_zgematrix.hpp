//=============================================================================
/*! double*_zgematrix operator */
inline _zgematrix operator*(const double& d, const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(mat.M*mat.N, d, mat.Array, 1);
  return mat;
}

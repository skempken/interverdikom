//=============================================================================
/*! double*_dgbmatrix operator */
inline _dgbmatrix operator*(const double& d, const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}

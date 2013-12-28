//=============================================================================
/*! double*_zgbmatrix operator */
inline _zgbmatrix operator*(const double& d, const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const double&, const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_((mat.KL+mat.KU+1)*mat.N, d, mat.Array, 1);
  return mat;
}
